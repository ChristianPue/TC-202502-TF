; ModuleID = 'EduCodeModule'
source_filename = "EduCodeModule"

@str_lit = private unnamed_addr constant [8 x i8] c"alfonso\00", align 1
@.str = private constant [6 x i8] c"%255s\00"
@.str.1 = private constant [3 x i8] c"%d\00"
@str_lit.2 = private unnamed_addr constant [6 x i8] c"Hola \00", align 1
@str_lit.3 = private unnamed_addr constant [15 x i8] c"!, tu edad es \00", align 1
@.str.4 = private constant [3 x i8] c"%s\00"
@.str.5 = private constant [3 x i8] c"%s\00"
@.str.6 = private constant [3 x i8] c"%s\00"
@.str.7 = private constant [3 x i8] c"%d\00"
@.str.8 = private constant [2 x i8] c"\0A\00"

declare i32 @printf(ptr, ...)

declare i32 @scanf(ptr, ...)

define i32 @main() {
entry:
  %edad = alloca i32, align 4
  %nombre = alloca ptr, align 8
  store ptr @str_lit, ptr %nombre, align 8
  store i32 30, ptr %edad, align 4
  %str_buffer = alloca [256 x i8], align 1
  %0 = getelementptr inbounds [256 x i8], ptr %str_buffer, i32 0, i32 0
  %1 = call i32 (ptr, ...) @scanf(ptr @.str, ptr %0)
  store ptr %0, ptr %nombre, align 8
  %2 = call i32 (ptr, ...) @scanf(ptr @.str.1, ptr %edad)
  %nombre1 = load ptr, ptr %nombre, align 8
  %edad2 = load i32, ptr %edad, align 4
  %3 = call i32 (ptr, ...) @printf(ptr @.str.4, ptr @str_lit.2)
  %4 = call i32 (ptr, ...) @printf(ptr @.str.5, ptr %nombre1)
  %5 = call i32 (ptr, ...) @printf(ptr @.str.6, ptr @str_lit.3)
  %6 = call i32 (ptr, ...) @printf(ptr @.str.7, i32 %edad2)
  %7 = call i32 (ptr, ...) @printf(ptr @.str.8)
  ret i32 0
}
