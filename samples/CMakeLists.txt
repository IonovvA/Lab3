file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_executable(samples ${srcs} ${hdrs} queue.h stack.h)


