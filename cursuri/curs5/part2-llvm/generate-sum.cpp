#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/FileSystem.h>

using namespace llvm;

Module* makeLLVMModule(const std::string&);

int main(int argc, char** argv) 
{	
	std::string filename("sum.ll");
	Module* Mod = makeLLVMModule(filename);
	std::error_code err;
	// Create output stream
	raw_fd_ostream output(Mod->getName(), err, sys::fs::OF_Text);
	// Print .ll file
	Mod->print(output, nullptr);
	return 0;

}


/* Code generation for the following function:

int sum(int x, int y)
{
	return x + y - 10;
}

 */

static LLVMContext context;

Module* makeLLVMModule(const std::string& llFile) 
{
	//Create Module and Builder
	Module* Mod = new Module(llFile, context); 
	IRBuilder<> Builder(context);
	Mod->setDataLayout("e-m:e-i64:64-f80:128-n8:16:32:64-S128");
 	Mod->setTargetTriple("x86_64-pc-linux-gnu");

	//Create IntType
	auto IntType = IntegerType::getInt32Ty(context);

	//Create sum's function prototype	
	std::vector<Type*> sum_args = { IntType, IntType };
	FunctionType* sum_func_type = FunctionType::get(
	/*Return Type*/ IntType, 
	/*Params*/ sum_args, 
	/*isVarArg*/ false);

	Function* sum_func = Function::Create(sum_func_type, GlobalValue::ExternalLinkage, "sum", Mod);
	sum_func->setCallingConv(CallingConv::C);
	
	Function::arg_iterator args = sum_func->arg_begin();
	Argument* int32_x = &(*args++);
	int32_x->setName("x");
	Argument* int32_y = &(*args++);
	int32_y->setName("y");
	
	//Create sum's body
	BasicBlock* entry = BasicBlock::Create(context, "entry", sum_func);
	Builder.SetInsertPoint(entry);
	//Reserve space on the stack for the arguments
	AllocaInst* x_ptr = Builder.CreateAlloca(IntType, nullptr, "x_ptr");
	x_ptr->setAlignment(Align(4));
	AllocaInst* y_ptr = Builder.CreateAlloca(IntType, nullptr, "y_ptr");
	y_ptr->setAlignment(Align(4));

	//Store the arguments on the stack
	Builder.CreateStore(int32_x, x_ptr);
	Builder.CreateStore(int32_y, y_ptr);

	//Load the values from the stack
	LoadInst* x_val = Builder.CreateLoad(IntType, x_ptr, false, "x_val");
	x_val->setAlignment(Align(4));
	LoadInst* y_val = Builder.CreateLoad(IntType, y_ptr, false, "y_val");
	y_val->setAlignment(Align(4));

	//Compute the sum
	Value* sum = Builder.CreateAdd(x_val, y_val, "sum");

	// Subtract 10
	Value* diff = Builder.CreateSub(sum, ConstantInt::get(IntType, 10));

	//Return sum's value
	Builder.CreateRet(diff);
	return Mod;
}
