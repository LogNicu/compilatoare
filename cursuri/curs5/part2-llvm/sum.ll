; ModuleID = 'sum.ll'
source_filename = "sum.ll"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

define i32 @sum(i32 %x, i32 %y) {
entry:
  %x_ptr = alloca i32, align 4
  %y_ptr = alloca i32, align 4
  store i32 %x, ptr %x_ptr, align 4
  store i32 %y, ptr %y_ptr, align 4
  %x_val = load i32, ptr %x_ptr, align 4
  %y_val = load i32, ptr %y_ptr, align 4
  %sum = add i32 %x_val, %y_val
  %0 = sub i32 %sum, 10
  ret i32 %0
}
