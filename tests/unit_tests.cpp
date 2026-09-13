#include <gtest/gtest.h>

extern "C" {
#include "interpreter.h"
}

class InterpreterTest : public ::testing::Test {
 protected:
  System sys;

  void SetUp() override {
    initialize_system(&sys);
  }
};

TEST_F(InterpreterTest, MovlConstantToRegister) {
  EXPECT_EQ(execute_movl(&sys, (char *)"$10", (char *)"%EAX"), SUCCESS);
  EXPECT_EQ(sys.registers[EAX], 10);
}

TEST_F(InterpreterTest, MovlRegisterToRegister) {
  sys.registers[EDX] = 7;
  EXPECT_EQ(execute_movl(&sys, (char *)"%EDX", (char *)"%EAX"), SUCCESS);
  EXPECT_EQ(sys.registers[EAX], 7);
}

TEST_F(InterpreterTest, MovlRejectsConstantDestination) {
  EXPECT_EQ(execute_movl(&sys, (char *)"$5", (char *)"$10"), INSTRUCTION_ERROR);
}

TEST_F(InterpreterTest, AddlAddsRegisters) {
  sys.registers[EAX] = 10;
  sys.registers[EDX] = 3;
  EXPECT_EQ(execute_addl(&sys, (char *)"%EDX", (char *)"%EAX"), SUCCESS);
  EXPECT_EQ(sys.registers[EAX], 13);
}

TEST_F(InterpreterTest, PushAndPopRoundTrip) {
  sys.registers[EAX] = 42;
  int esp_before = sys.registers[ESP];

  EXPECT_EQ(execute_push(&sys, (char *)"%EAX"), SUCCESS);
  EXPECT_EQ(sys.registers[ESP], esp_before - 4);

  sys.registers[ECX] = 0;
  EXPECT_EQ(execute_pop(&sys, (char *)"%ECX"), SUCCESS);
  EXPECT_EQ(sys.registers[ECX], 42);
  EXPECT_EQ(sys.registers[ESP], esp_before);
}

TEST_F(InterpreterTest, CmplSetsComparisonFlag) {
  sys.registers[EAX] = 13;
  sys.registers[ECX] = 2;
  // comparison_flag = dst - src = EAX - ECX = 11
  EXPECT_EQ(execute_cmpl(&sys, (char *)"%ECX", (char *)"%EAX"), SUCCESS);
  EXPECT_EQ(sys.comparison_flag, 11);
}

TEST_F(InterpreterTest, GetRegisterByName) {
  EXPECT_EQ(get_register_by_name("%EAX"), EAX);
  EXPECT_EQ(get_register_by_name("%ESP"), ESP);
  EXPECT_EQ(get_register_by_name("%BAD"), NOT_REG);
}

TEST_F(InterpreterTest, GetMemoryTypeConstant) {
  MemoryType mt = get_memory_type("$25");
  EXPECT_EQ(mt.type, CONST);
  EXPECT_EQ(mt.value, 25);
  EXPECT_EQ(mt.reg, NOT_REG);
}

TEST_F(InterpreterTest, GetMemoryTypeRegister) {
  MemoryType mt = get_memory_type("%EDX");
  EXPECT_EQ(mt.type, REG);
  EXPECT_EQ(mt.reg, EDX);
}
