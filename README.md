# Monitor Control
Project to turn monitors on and off on Windows using nirsoft/multimonitorTool. Can be executed via command line interface or with program arguments. Takes switches -1, -2, -3 for activation of the respective monitor or -off for none.

To add this script to startup or shutdown routines please create batch files with the following contents:

```bat
DriveLetter:
cd "DriveLetter:\Path_to_executable_folder"
del logfile
call MonitorControl.exe {options} >> logfile
```


Then place those scripts into ```C:\WINDOWS\System32\GroupPolicy\Machine\Scripts\Startup``` and ```C:\WINDOWS\System32\GroupPolicy\Machine\Scripts\Shutdown``` respectively in order to function properly.