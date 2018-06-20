; ModuleID = 'dog-decaf'
source_filename = "dog-decaf"

%struct.string = type { i32, i8* }

declare i32 @readint()

declare i32 @refint(i32)

declare %struct.string* @readline()

declare void @printss(%struct.string*)

define i32 @main() {
entry:
  %local_decl = alloca i32
  store i32 42, i32* %local_decl
  %ld = load i32, i32* %local_decl
  store i32 %ld, i32* %local_decl
  %ld1 = load i32, i32* %local_decl
  ret i32 %ld1
}
