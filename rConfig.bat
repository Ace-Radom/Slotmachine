@echo off
 
@rem this bat need .ini path as the first parameter
@rem the second parameter is the config_key 
@rem will return key_value

set CONFIG_FILE_PARAM=%1

for /f "usebackq skip=1 tokens=1,2 delims==" %%a in (%CONFIG_FILE_PARAM%) do (
    if %2==%%a set %3=%%b
)