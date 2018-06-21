; ModuleID = 'runtime.c'
source_filename = "runtime.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.string = type { i32, i8* }
%struct.__sym_table = type { i32, %struct.__entry* }
%struct.__entry = type { i32, i8* }

@global = common global i32 0, align 4
@global_arr = global i32* @global, align 8
@global_arr_ptr = global i8* bitcast (i32* @global to i8*), align 8
@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.1 = private unnamed_addr constant [7 x i8] c"ref=%d\00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.3 = private unnamed_addr constant [8 x i8] c"(%d)%s \00", align 1
@.str.4 = private unnamed_addr constant [4 x i8] c"%s \00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.str.6 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.str.7 = private unnamed_addr constant [4 x i8] c"%d \00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"%lf \00", align 1
@.str.9 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@.str.10 = private unnamed_addr constant [10 x i8] c"runtime.c\00", align 1
@__PRETTY_FUNCTION__.string_cat = private unnamed_addr constant [39 x i8] c"string *string_cat(string *, string *)\00", align 1
@.str.11 = private unnamed_addr constant [2 x i8] c"b\00", align 1

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define i32 @readint() #0 {
  %1 = alloca i32, align 4
  %2 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i32* %1)
  %3 = load i32, i32* %1, align 4
  ret i32 %3
}

declare i32 @__isoc99_scanf(i8*, ...) #1

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define i32 @refint(i32) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i32 0, i32 0), i32 %3)
  %5 = load i32, i32* %2, align 4
  ret i32 %5
}

declare i32 @printf(i8*, ...) #1

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define i8* @dog_malloc(i32) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = sext i32 %3 to i64
  %5 = call noalias i8* @malloc(i64 %4) #6
  ret i8* %5
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define %struct.string* @readline() #0 {
  %1 = alloca i8*, align 8
  %2 = alloca %struct.string*, align 8
  %3 = call noalias i8* @malloc(i64 100) #6
  store i8* %3, i8** %1, align 8
  %4 = load i8*, i8** %1, align 8
  %5 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.2, i32 0, i32 0), i8* %4)
  %6 = call i8* @dog_malloc(i32 16)
  %7 = bitcast i8* %6 to %struct.string*
  store %struct.string* %7, %struct.string** %2, align 8
  %8 = load i8*, i8** %1, align 8
  %9 = load %struct.string*, %struct.string** %2, align 8
  %10 = getelementptr inbounds %struct.string, %struct.string* %9, i32 0, i32 1
  store i8* %8, i8** %10, align 8
  %11 = load i8*, i8** %1, align 8
  %12 = call i64 @strlen(i8* %11) #7
  %13 = trunc i64 %12 to i32
  %14 = load %struct.string*, %struct.string** %2, align 8
  %15 = getelementptr inbounds %struct.string, %struct.string* %14, i32 0, i32 0
  store i32 %13, i32* %15, align 8
  %16 = load %struct.string*, %struct.string** %2, align 8
  ret %struct.string* %16
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #3

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define void @printstring(%struct.string*) #0 {
  %2 = alloca %struct.string*, align 8
  store %struct.string* %0, %struct.string** %2, align 8
  %3 = load %struct.string*, %struct.string** %2, align 8
  %4 = getelementptr inbounds %struct.string, %struct.string* %3, i32 0, i32 0
  %5 = load i32, i32* %4, align 8
  %6 = load %struct.string*, %struct.string** %2, align 8
  %7 = getelementptr inbounds %struct.string, %struct.string* %6, i32 0, i32 1
  %8 = load i8*, i8** %7, align 8
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.3, i32 0, i32 0), i32 %5, i8* %8)
  ret void
}

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define void @printbool(i1 zeroext) #0 {
  %2 = alloca i8, align 1
  %3 = zext i1 %0 to i8
  store i8 %3, i8* %2, align 1
  %4 = load i8, i8* %2, align 1
  %5 = trunc i8 %4 to i1
  %6 = zext i1 %5 to i64
  %7 = select i1 %5, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0)
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i8* %7)
  ret void
}

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define void @printint(i32) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0), i32 %3)
  ret void
}

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define void @printdouble(double) #0 {
  %2 = alloca double, align 8
  store double %0, double* %2, align 8
  %3 = load double, double* %2, align 8
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i32 0, i32 0), double %3)
  ret void
}

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define %struct.string* @string_cat(%struct.string*, %struct.string*) #0 {
  %3 = alloca %struct.string*, align 8
  %4 = alloca %struct.string*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i8*, align 8
  %7 = alloca %struct.string*, align 8
  store %struct.string* %0, %struct.string** %3, align 8
  store %struct.string* %1, %struct.string** %4, align 8
  %8 = load %struct.string*, %struct.string** %3, align 8
  %9 = icmp ne %struct.string* %8, null
  br i1 %9, label %10, label %11

; <label>:10:                                     ; preds = %2
  br label %12

; <label>:11:                                     ; preds = %2
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.10, i32 0, i32 0), i32 58, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.string_cat, i32 0, i32 0)) #8
  unreachable

; <label>:12:                                     ; preds = %10
  %13 = load %struct.string*, %struct.string** %4, align 8
  %14 = icmp ne %struct.string* %13, null
  br i1 %14, label %15, label %16

; <label>:15:                                     ; preds = %12
  br label %17

; <label>:16:                                     ; preds = %12
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.10, i32 0, i32 0), i32 59, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.string_cat, i32 0, i32 0)) #8
  unreachable

; <label>:17:                                     ; preds = %15
  %18 = load %struct.string*, %struct.string** %3, align 8
  %19 = getelementptr inbounds %struct.string, %struct.string* %18, i32 0, i32 0
  %20 = load i32, i32* %19, align 8
  %21 = load %struct.string*, %struct.string** %4, align 8
  %22 = getelementptr inbounds %struct.string, %struct.string* %21, i32 0, i32 0
  %23 = load i32, i32* %22, align 8
  %24 = add nsw i32 %20, %23
  store i32 %24, i32* %5, align 4
  %25 = load i32, i32* %5, align 4
  %26 = add nsw i32 %25, 1
  %27 = call i8* @dog_malloc(i32 %26)
  store i8* %27, i8** %6, align 8
  %28 = call i8* @dog_malloc(i32 16)
  %29 = bitcast i8* %28 to %struct.string*
  store %struct.string* %29, %struct.string** %7, align 8
  %30 = load i8*, i8** %6, align 8
  %31 = load %struct.string*, %struct.string** %7, align 8
  %32 = getelementptr inbounds %struct.string, %struct.string* %31, i32 0, i32 1
  store i8* %30, i8** %32, align 8
  %33 = load i8*, i8** %6, align 8
  %34 = load %struct.string*, %struct.string** %3, align 8
  %35 = getelementptr inbounds %struct.string, %struct.string* %34, i32 0, i32 1
  %36 = load i8*, i8** %35, align 8
  %37 = call i8* @strcpy(i8* %33, i8* %36) #6
  %38 = load i8*, i8** %6, align 8
  %39 = load %struct.string*, %struct.string** %3, align 8
  %40 = getelementptr inbounds %struct.string, %struct.string* %39, i32 0, i32 0
  %41 = load i32, i32* %40, align 8
  %42 = sext i32 %41 to i64
  %43 = getelementptr inbounds i8, i8* %38, i64 %42
  %44 = load %struct.string*, %struct.string** %4, align 8
  %45 = getelementptr inbounds %struct.string, %struct.string* %44, i32 0, i32 1
  %46 = load i8*, i8** %45, align 8
  %47 = call i8* @strcpy(i8* %43, i8* %46) #6
  %48 = load i32, i32* %5, align 4
  %49 = load %struct.string*, %struct.string** %7, align 8
  %50 = getelementptr inbounds %struct.string, %struct.string* %49, i32 0, i32 0
  store i32 %48, i32* %50, align 8
  %51 = load %struct.string*, %struct.string** %7, align 8
  ret %struct.string* %51
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #4

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #2

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define i8* @load_ptr(%struct.__sym_table*, i32) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca %struct.__sym_table*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca %struct.__entry, align 8
  store %struct.__sym_table* %0, %struct.__sym_table** %4, align 8
  store i32 %1, i32* %5, align 4
  store i32 0, i32* %6, align 4
  %10 = load %struct.__sym_table*, %struct.__sym_table** %4, align 8
  %11 = getelementptr inbounds %struct.__sym_table, %struct.__sym_table* %10, i32 0, i32 0
  %12 = load i32, i32* %11, align 8
  store i32 %12, i32* %7, align 4
  br label %13

; <label>:13:                                     ; preds = %37, %2
  %14 = load i32, i32* %7, align 4
  %15 = load i32, i32* %6, align 4
  %16 = icmp ne i32 %14, %15
  br i1 %16, label %17, label %38

; <label>:17:                                     ; preds = %13
  %18 = load i32, i32* %6, align 4
  %19 = load i32, i32* %7, align 4
  %20 = add nsw i32 %18, %19
  %21 = sdiv i32 %20, 2
  store i32 %21, i32* %8, align 4
  %22 = load %struct.__sym_table*, %struct.__sym_table** %4, align 8
  %23 = getelementptr inbounds %struct.__sym_table, %struct.__sym_table* %22, i32 0, i32 1
  %24 = load %struct.__entry*, %struct.__entry** %23, align 8
  %25 = load i32, i32* %8, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds %struct.__entry, %struct.__entry* %24, i64 %26
  %28 = getelementptr inbounds %struct.__entry, %struct.__entry* %27, i32 0, i32 0
  %29 = load i32, i32* %28, align 8
  %30 = load i32, i32* %5, align 4
  %31 = icmp slt i32 %29, %30
  br i1 %31, label %32, label %34

; <label>:32:                                     ; preds = %17
  %33 = load i32, i32* %8, align 4
  store i32 %33, i32* %6, align 4
  br label %37

; <label>:34:                                     ; preds = %17
  %35 = load i32, i32* %8, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %7, align 4
  br label %37

; <label>:37:                                     ; preds = %34, %32
  br label %13

; <label>:38:                                     ; preds = %13
  %39 = load %struct.__sym_table*, %struct.__sym_table** %4, align 8
  %40 = getelementptr inbounds %struct.__sym_table, %struct.__sym_table* %39, i32 0, i32 1
  %41 = load %struct.__entry*, %struct.__entry** %40, align 8
  %42 = load i32, i32* %6, align 4
  %43 = sext i32 %42 to i64
  %44 = getelementptr inbounds %struct.__entry, %struct.__entry* %41, i64 %43
  %45 = bitcast %struct.__entry* %9 to i8*
  %46 = bitcast %struct.__entry* %44 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %45, i8* %46, i64 16, i32 8, i1 false)
  %47 = getelementptr inbounds %struct.__entry, %struct.__entry* %9, i32 0, i32 0
  %48 = load i32, i32* %47, align 8
  %49 = load i32, i32* %5, align 4
  %50 = icmp eq i32 %48, %49
  br i1 %50, label %51, label %54

; <label>:51:                                     ; preds = %38
  %52 = getelementptr inbounds %struct.__entry, %struct.__entry* %9, i32 0, i32 1
  %53 = load i8*, i8** %52, align 8
  store i8* %53, i8** %3, align 8
  br label %55

; <label>:54:                                     ; preds = %38
  store i8* null, i8** %3, align 8
  br label %55

; <label>:55:                                     ; preds = %54, %51
  %56 = load i8*, i8** %3, align 8
  ret i8* %56
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define void @fuck() #0 {
  %1 = alloca i32 (i32)*, align 8
  %2 = alloca i32, align 4
  store i32 (i32)* null, i32 (i32)** %1, align 8
  %3 = load i32 (i32)*, i32 (i32)** %1, align 8
  %4 = call i32 %3(i32 5)
  store i32 %4, i32* %2, align 4
  ret void
}

attributes #0 = { noinline nounwind optnone sspstrong uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }
attributes #8 = { noreturn nounwind }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{!"clang version 6.0.0 (tags/RELEASE_600/final)"}
