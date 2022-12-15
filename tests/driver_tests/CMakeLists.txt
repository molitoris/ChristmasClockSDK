
add_executable(test_ir test_ir/test_receiver.cpp)

target_link_libraries(test_ir
 PRIVATE
  GTest::GTest
  ir)

add_test(ir_gtests test_ir)