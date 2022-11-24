@set arduino_config_path=arduino_config.ini

@echo ========= call rConfig.bat =========

@set board_key=board
@set board_type=0

@set port_key=port
@set port_num=0

@set file_key=file
@set file_path=0

@set Compiler_key=CompilerPath
@set Compiler_path=0

@call .\rConfig.bat %arduino_config_path% %board_key% board_type
@echo %board_key% = %board_type%

@call .\rConfig.bat %arduino_config_path% %port_key% port_num
@echo %port_key% = %port_num%

@call .\rConfig.bat %arduino_config_path% %file_key% file_path
@echo %file_key% = %file_path%

@call .\rConfig.bat %arduino_config_path% %Compiler_key% Compiler_path
@echo %Compiler_key% = %Compiler_path%

@rem read all parameters arduino debug program needs from arduino_config.ini    

@echo ======== call arduino_debug ========

call %Compiler_path% --board %board_type% --port %port_num% --upload %file_path%
@rem call arduino debug program to verify