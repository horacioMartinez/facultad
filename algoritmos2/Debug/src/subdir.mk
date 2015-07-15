################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/01_argc.c \
../src/02_argc2.c \
../src/03_generar_vector.c \
../src/04_copiar.c \
../src/05_escribir_vector.c \
../src/06_leer_vector.c \
../src/07_leer_vector2.c \
../src/1-1-fib-recursivo.c \
../src/1-2-fib-iterativo.c \
../src/1.c \
../src/2-1-reverse-recursivo.c \
../src/2-2-reverse-goto.c \
../src/2-3-reverse-iterativo.c \
../src/3-1-mergrsort-rec.c \
../src/3-2-meresort-iter.c \
../src/abb.c \
../src/asd.c \
../src/clase_malloc_memoria_invalida.c \
../src/clase_malloc_realloc.c \
../src/coherencia_parentesis.c \
../src/cola.c \
../src/cola_con_pilas.c \
../src/ej1_pruebas.c \
../src/ejemplos-tail.c \
../src/fac-iterativo.c \
../src/fac-recursivo.c \
../src/fac-tailrec.c \
../src/funciones.c \
../src/hash.c \
../src/heap.c \
../src/lista.c \
../src/pila.c \
../src/prueba_abb.c \
../src/prueba_cola.c \
../src/prueba_hash.c \
../src/prueba_heap.c \
../src/prueba_lista.c \
../src/prueba_pila.c \
../src/pruebas_funciones.c \
../src/struct.c \
../src/tp0.c \
../src/tp1.c \
../src/vector_dinamico.c 

OBJS += \
./src/01_argc.o \
./src/02_argc2.o \
./src/03_generar_vector.o \
./src/04_copiar.o \
./src/05_escribir_vector.o \
./src/06_leer_vector.o \
./src/07_leer_vector2.o \
./src/1-1-fib-recursivo.o \
./src/1-2-fib-iterativo.o \
./src/1.o \
./src/2-1-reverse-recursivo.o \
./src/2-2-reverse-goto.o \
./src/2-3-reverse-iterativo.o \
./src/3-1-mergrsort-rec.o \
./src/3-2-meresort-iter.o \
./src/abb.o \
./src/asd.o \
./src/clase_malloc_memoria_invalida.o \
./src/clase_malloc_realloc.o \
./src/coherencia_parentesis.o \
./src/cola.o \
./src/cola_con_pilas.o \
./src/ej1_pruebas.o \
./src/ejemplos-tail.o \
./src/fac-iterativo.o \
./src/fac-recursivo.o \
./src/fac-tailrec.o \
./src/funciones.o \
./src/hash.o \
./src/heap.o \
./src/lista.o \
./src/pila.o \
./src/prueba_abb.o \
./src/prueba_cola.o \
./src/prueba_hash.o \
./src/prueba_heap.o \
./src/prueba_lista.o \
./src/prueba_pila.o \
./src/pruebas_funciones.o \
./src/struct.o \
./src/tp0.o \
./src/tp1.o \
./src/vector_dinamico.o 

C_DEPS += \
./src/01_argc.d \
./src/02_argc2.d \
./src/03_generar_vector.d \
./src/04_copiar.d \
./src/05_escribir_vector.d \
./src/06_leer_vector.d \
./src/07_leer_vector2.d \
./src/1-1-fib-recursivo.d \
./src/1-2-fib-iterativo.d \
./src/1.d \
./src/2-1-reverse-recursivo.d \
./src/2-2-reverse-goto.d \
./src/2-3-reverse-iterativo.d \
./src/3-1-mergrsort-rec.d \
./src/3-2-meresort-iter.d \
./src/abb.d \
./src/asd.d \
./src/clase_malloc_memoria_invalida.d \
./src/clase_malloc_realloc.d \
./src/coherencia_parentesis.d \
./src/cola.d \
./src/cola_con_pilas.d \
./src/ej1_pruebas.d \
./src/ejemplos-tail.d \
./src/fac-iterativo.d \
./src/fac-recursivo.d \
./src/fac-tailrec.d \
./src/funciones.d \
./src/hash.d \
./src/heap.d \
./src/lista.d \
./src/pila.d \
./src/prueba_abb.d \
./src/prueba_cola.d \
./src/prueba_hash.d \
./src/prueba_heap.d \
./src/prueba_lista.d \
./src/prueba_pila.d \
./src/pruebas_funciones.d \
./src/struct.d \
./src/tp0.d \
./src/tp1.d \
./src/vector_dinamico.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


