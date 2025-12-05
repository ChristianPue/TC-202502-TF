; ModuleID = 'EduCodeModule'
source_filename = "EduCodeModule"

@str_lit = private unnamed_addr constant [5 x i8] c"Juan\00", align 1
@str_lit.1 = private unnamed_addr constant [5 x i8] c"Hola\00", align 1
@str_lit.2 = private unnamed_addr constant [11 x i8] c"tu edad es\00", align 1
@.str = private constant [4 x i8] c"%s\0A\00"
@.str.3 = private constant [4 x i8] c"%s\0A\00"
@.str.4 = private constant [4 x i8] c"%s\0A\00"
@.str.5 = private constant [4 x i8] c"%d\0A\00"
@str_lit.6 = private unnamed_addr constant [19 x i8] c"Eres mayor de edad\00", align 1
@.str.7 = private constant [4 x i8] c"%s\0A\00"
@str_lit.8 = private unnamed_addr constant [19 x i8] c"Eres menor de edad\00", align 1
@.str.9 = private constant [4 x i8] c"%s\0A\00"
@.str.10 = private constant [4 x i8] c"%d\0A\00"
@.str.11 = private constant [3 x i8] c"%s\00"
@.str.12 = private constant [3 x i8] c"%d\00"
@.str.13 = private constant [4 x i8] c"%d\0A\00"

declare i32 @printf(ptr, ...)

declare i32 @scanf(ptr, ...)

define i32 @main() {
entry:
  %i = alloca i32, align 4
  %num = alloca i32, align 4
  %num_idx = alloca i32, align 4
  %numeros = alloca [5 x i32], align 4
  %nombre = alloca ptr, align 8
  %precio = alloca float, align 4
  %edad = alloca i32, align 4
  store i32 25, ptr %edad, align 4
  store float 0x4058FCCCC0000000, ptr %precio, align 4
  store ptr @str_lit, ptr %nombre, align 8
  %nombre1 = load ptr, ptr %nombre, align 8
  %edad2 = load i32, ptr %edad, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @.str, ptr @str_lit.1)
  %1 = call i32 (ptr, ...) @printf(ptr @.str.3, ptr %nombre1)
  %2 = call i32 (ptr, ...) @printf(ptr @.str.4, ptr @str_lit.2)
  %3 = call i32 (ptr, ...) @printf(ptr @.str.5, i32 %edad2)
  %edad3 = load i32, ptr %edad, align 4
  %cmptmp = icmp sge i32 %edad3, 18
  br i1 %cmptmp, label %then, label %else

then:                                             ; preds = %entry
  %4 = call i32 (ptr, ...) @printf(ptr @.str.7, ptr @str_lit.6)
  br label %ifcont

else:                                             ; preds = %entry
  %5 = call i32 (ptr, ...) @printf(ptr @.str.9, ptr @str_lit.8)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %6 = getelementptr inbounds [5 x i32], ptr %numeros, i32 0, i32 0
  store i32 1, ptr %6, align 4
  %7 = getelementptr inbounds [5 x i32], ptr %numeros, i32 0, i32 1
  store i32 2, ptr %7, align 4
  %8 = getelementptr inbounds [5 x i32], ptr %numeros, i32 0, i32 2
  store i32 3, ptr %8, align 4
  %9 = getelementptr inbounds [5 x i32], ptr %numeros, i32 0, i32 3
  store i32 4, ptr %9, align 4
  %10 = getelementptr inbounds [5 x i32], ptr %numeros, i32 0, i32 4
  store i32 5, ptr %10, align 4
  store i32 0, ptr %num_idx, align 4
  br label %foreachcond

foreachcond:                                      ; preds = %foreachbody, %ifcont
  %11 = load i32, ptr %num_idx, align 4
  %12 = icmp slt i32 %11, 5
  br i1 %12, label %foreachbody, label %foreachend

foreachbody:                                      ; preds = %foreachcond
  %13 = getelementptr inbounds [5 x i32], ptr %numeros, i32 0, i32 %11
  %14 = load i32, ptr %13, align 4
  store i32 %14, ptr %num, align 4
  %num4 = load i32, ptr %num, align 4
  %multmp = mul i32 %num4, 2
  %15 = call i32 (ptr, ...) @printf(ptr @.str.10, i32 %multmp)
  %16 = load i32, ptr %num_idx, align 4
  %17 = add i32 %16, 1
  store i32 %17, ptr %num_idx, align 4
  br label %foreachcond

foreachend:                                       ; preds = %foreachcond
  %18 = call i32 (ptr, ...) @scanf(ptr @.str.11, ptr %nombre)
  %19 = call i32 (ptr, ...) @scanf(ptr @.str.12, ptr %edad)
  store i32 0, ptr %i, align 4
  br label %loopcond

loopcond:                                         ; preds = %loopbody, %foreachend
  %i5 = load i32, ptr %i, align 4
  %cmptmp6 = icmp slt i32 %i5, 5
  br i1 %cmptmp6, label %loopbody, label %loopend

loopbody:                                         ; preds = %loopcond
  %i7 = load i32, ptr %i, align 4
  %elemPtr = getelementptr inbounds [5 x i32], ptr %numeros, i32 0, i32 %i7
  %elemVal = load i32, ptr %elemPtr, align 4
  %20 = call i32 (ptr, ...) @printf(ptr @.str.13, i32 %elemVal)
  %i8 = load i32, ptr %i, align 4
  %addtmp = add i32 %i8, 1
  store i32 %addtmp, ptr %i, align 4
  br label %loopcond

loopend:                                          ; preds = %loopcond
  ret i32 0
}
