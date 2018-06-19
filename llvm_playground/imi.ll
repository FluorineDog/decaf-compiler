; ModuleID = 'my cool jit'
source_filename = "my cool jit"

%struct.string = type { i32, i8* }
%struct.string.0 = type { i32, i8* }

declare i32 @readint()

declare i32 @refint(i32)

declare %struct.string* @readline()

declare void @printss(%struct.string*)

define i32 @main() {
god_see:
  %node = alloca %struct.string*
  %node2 = alloca %struct.string.0
  %calltmp = call %struct.string* @readline()
  store %struct.string* %calltmp, %struct.string** %node
  %ld = load %struct.string*, %struct.string** %node
  %lenAddr = getelementptr %struct.string, %struct.string* %ld, i32 0, i32 0
  %len = load i32, i32* %lenAddr
  %mem2 = add i32 %len, %len
  store i32 %mem2, i32* %lenAddr
  call void @printss(%struct.string* %ld)
  %tmp = alloca i32
  store i32 100, i32* %tmp
  %ld1 = load i32, i32* %tmp
  %calltmp2 = call i32 @readint()
  %addtmp = add i32 %ld1, %calltmp2
  %calltmp3 = call i32 @refint(i32 %addtmp)
  ret i32 %calltmp3
}
