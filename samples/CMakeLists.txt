file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_executable(samples ${srcs} ${hdrs} arithmetic_expression.h queue.h stack.h)


