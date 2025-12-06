; ModuleID = 'EduCodeModule'
source_filename = "EduCodeModule"

@str_lit = private unnamed_addr constant [5 x i8] c"Juan\00", align 1
@str_lit.1 = private unnamed_addr constant [6 x i8] c"Hola \00", align 1
@.str = private constant [3 x i8] c"%s\00"
@.str.2 = private constant [3 x i8] c"%s\00"
@.str.3 = private constant [2 x i8] c"\0A\00"
@str_lit.4 = private unnamed_addr constant [12 x i8] c"Tu edad es \00", align 1
@.str.5 = private constant [3 x i8] c"%s\00"
@.str.6 = private constant [3 x i8] c"%d\00"
@.str.7 = private constant [2 x i8] c"\0A\00"
@str_lit.8 = private unnamed_addr constant [14 x i8] c"Tu precio es \00", align 1
@.str.9 = private constant [3 x i8] c"%s\00"
@.str.10 = private constant [5 x i8] c"%.2f\00"
@.str.11 = private constant [2 x i8] c"\0A\00"

declare i32 @printf(ptr, ...)

declare i32 @scanf(ptr, ...)

define i32 @main() {
entry:
  %nombre = alloca ptr, align 8
  %precio = alloca float, align 4
  %edad = alloca i32, align 4
  store i32 25, ptr %edad, align 4
  store float 0x4058FCCCC0000000, ptr %precio, align 4
  store ptr @str_lit, ptr %nombre, align 8
  %nombre1 = load ptr, ptr %nombre, align 8
  %0 = call i32 (ptr, ...) @printf(ptr @.str, ptr @str_lit.1)
  %1 = call i32 (ptr, ...) @printf(ptr @.str.2, ptr %nombre1)
  %2 = call i32 (ptr, ...) @printf(ptr @.str.3)
  %edad2 = load i32, ptr %edad, align 4
  %3 = call i32 (ptr, ...) @printf(ptr @.str.5, ptr @str_lit.4)
  %4 = call i32 (ptr, ...) @printf(ptr @.str.6, i32 %edad2)
  %5 = call i32 (ptr, ...) @printf(ptr @.str.7)
  %precio3 = load float, ptr %precio, align 4
  %6 = call i32 (ptr, ...) @printf(ptr @.str.9, ptr @str_lit.8)
  %7 = fpext float %precio3 to double
  %8 = call i32 (ptr, ...) @printf(ptr @.str.10, double %7)
  %9 = call i32 (ptr, ...) @printf(ptr @.str.11)
  ret i32 0
}
