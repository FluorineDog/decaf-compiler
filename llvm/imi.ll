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
  %node = alloca %struct.string.0*
  %calltmp = call %struct.string* @readline()
  store %struct.string* %calltmp, %struct.string.0** %node
  %ld = load %struct.string.0*, %struct.string.0** %node
  call void @printss(%struct.string.0* %ld)
  %tmp = alloca i32
  store i32 100, i32* %tmp
  %ld1 = load i32, i32* %tmp
  %calltmp2 = call i32 @readint()
  %addtmp = add i32 %ld1, %calltmp2
  %calltmp3 = call i32 @refint(i32 %addtmp)
  ret i32 %calltmp3
}
