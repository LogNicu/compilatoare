//
// Created by nicu on 20.12.2023.
//

#ifndef ANOTHER_LL_TEST_STATEMENT_H
#define ANOTHER_LL_TEST_STATEMENT_H


class Statement {
public:
    virtual void print(int level = 0) = 0;
    virtual ~Statement() {};
};


#endif //ANOTHER_LL_TEST_STATEMENT_H
