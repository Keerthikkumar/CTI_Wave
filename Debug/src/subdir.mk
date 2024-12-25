################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CTI_Wave.cpp \
../src/File_Handling.cpp \
../src/Sample_Wave.cpp \
../src/TimeSrc.cpp 

CPP_DEPS += \
./src/CTI_Wave.d \
./src/File_Handling.d \
./src/Sample_Wave.d \
./src/TimeSrc.d 

OBJS += \
./src/CTI_Wave.o \
./src/File_Handling.o \
./src/Sample_Wave.o \
./src/TimeSrc.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/CTI_Wave.d ./src/CTI_Wave.o ./src/File_Handling.d ./src/File_Handling.o ./src/Sample_Wave.d ./src/Sample_Wave.o ./src/TimeSrc.d ./src/TimeSrc.o

.PHONY: clean-src

