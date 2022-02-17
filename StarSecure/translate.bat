cd Output\Objects

@SET fromelf_exe="D:\Keil_v536\ARM\ARMCLANG\bin\fromelf.exe"
@SET bk_encrypt_exe="..\..\..\tools\beken_encrypt\encrypt_3231s.exe"
@SET srec_cat_exe="..\..\..\tools\srecord\srec_cat.exe"

@if not exist "fromelf.exe" (
	@echo [TIP]"fromelf.exe file not found in system default path"
	@if not exist %fromelf_exe% (
		@echo [ERROR] %fromelf_exe% is no find!!!!              Error
		@echo [TIP]abnormal termination
		exit
	) else (
		@echo [TIP]fromelf_exe path: %fromelf_exe%
	)
) else (
	@fromelf_exe="fromelf.exe"
)

@if not exist %bk_encrypt_exe% (
	@echo [ERROR] %bk_encrypt_exe% is not exist!!!              Error
	exit
)

@if exist ".\StarSecure.bin" (
	del ".\StarSecure.bin"
)

@if not exist ".\StarSecure.axf" (
	echo ".\StarSecure.axf" is not exist
	exit
)

%fromelf_exe% ".\StarSecure.axf" --output .\StarSecure.bin --bin
@if not exist .\StarSecure.bin (
	echo .\StarSecure.bin is not exist                -->      Error
	exit
)
%bk_encrypt_exe% StarSecure.bin 00000000 > StarSecure_encrypt_temp.log
%fromelf_exe%  --text -a -c --output StarSecure.txt  StarSecure.axf
del StarSecure_encrypt_temp.log

@if not exist "..\..\..\StarNoSecure\Output\Objects\StarNoSecure.bin" (
	echo "..\..\..\StarNoSecure\Output\Objects\StarNoSecure.bin" is not exist      -->      Error
	exit
)

%srec_cat_exe% -output secure_with_nosecure.bin -binary ".\StarSecure.bin" -binary -fill 0xff 0x00000000 0x0000F000 "..\..\..\StarNoSecure\Output\Objects\StarNoSecure.bin" -binary -offset 0x0000F000

@if exist "../../../build/" (
	@copy "./StarSecure.bin" "../../../build/StarSecure.bin"
	@copy "./secure_with_nosecure.bin" "../../../build/secure_and_nosecure_all.bin"
)

exit

