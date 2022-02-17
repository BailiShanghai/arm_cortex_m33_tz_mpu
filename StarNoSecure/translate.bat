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

@if exist "StarNoSecure.bin" (
	del "StarNoSecure.bin"
)

@if not exist ".\StarNoSecure.axf" (
	echo ".\StarNoSecure.axf" is not exist              --->    Error
	exit
)

%fromelf_exe% StarNoSecure.axf --output StarNoSecure.bin --bin
@if not exist ".\StarNoSecure.bin" (
	echo ".\StarNoSecure.bin" is not exist              --->    Error
	exit
)

@if not exist "..\..\..\StarSecure\Output\Objects\StarSecure.bin" (
	echo "..\..\..\StarSecure\Output\Objects\StarSecure.bin" is not exist              --->    Error
	exit
)
%srec_cat_exe% -output secure_with_nosecure.bin -binary "..\..\..\StarSecure\Output\Objects\StarSecure.bin" -binary -fill 0xff 0x00000000 0x0000F000 StarNoSecure.bin -binary -offset 0x0000F000
%bk_encrypt_exe% StarNoSecure.bin 00000000 > ".\StarNoSecure_encrypt_temp.log"
%fromelf_exe%  --text -a -c --output StarNoSecure.txt  StarNoSecure.axf
@if exist ".\StarNoSecure_encrypt_temp.log" (
	@del ".\StarNoSecure_encrypt_temp.log"
)

@if exist "../../../build/" (
	@copy "./StarNoSecure.bin" "../../../build/StarNoSecure.bin"
	@copy "./secure_with_nosecure.bin" "../../../build/secure_and_nosecure_all.bin"
)

exit

