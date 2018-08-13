# UPupilLabsVR
Plugin for connecting to Pupil Labs VR using the ZeroMQ library

<b>Installation</b>
<br/>1.Download this in to the ..\Plugins folder of your Project
<br/>2.In Project.build.cs file add "UPupilLabsVR" in the PublicDependecyModulesNames
<b>Callibration</b>
https://www.youtube.com/watch?v=6sWmOcGMDTk
For the Moment all info is logged in the console.
For The Moment if you want to change where you connect you need to go in FPupilLabsUtils.h and change this fields
	<br/>std::string Addr = "tcp://127.0.0.1:";//ToDo UPROPERTY Options
	<br/>std::string PupilTopic = u8"gaze"; //TODO Implement Options With UObject
<br/>With these:
  <br/>	//string filter = u8"gaze";
  <br/>	//string filter = u8"notify";
  <br/>	//string filter = u8"pupil";
  <br/>	//string filter = u8"logging"; 
Although the current other structures aside from gaze are not implemented #TODO
  
  Currently uses port 55555 on localhost

Common Errors:

Can't compile C++ : missing "alts.lib" - Solution : Open Visual Studio Installer -> Select Desktop development with c++ -> Select MFC and Atl Support + VC++ 2015.3v 140 toolset for desktop and install them
