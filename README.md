# Gsoc 2018

Brief Objectives.
1. Create a GUI for the research institute that can confortobly edit object tags and visualize their properties.-
2. Have the eye-tracking plugin work with Pupil Head Mounted Eyetracker.
# What has been done.
1. Integration of an editor gui with the existing tags modules and their capabilities.
2. Integration of the Pupil Eye-tracker in Unreal with limited functionality.
3. Conveying of the 2 modules.
# Todo
1. Open the connection procedures through a much more aproachable api.
2. Obtain more reliable calibration procedure.
3. Make an in game GUI for user hot swaps and modifications on the fly.
4. Extend the editor to include topic subscriptions and better visualizations.

# UPupilLabs Utils

Unreal Engine Editor Modules for viewing specific tags in an editor module. Under these tags that can be visualised and edited different properties of objects can be edited. Including the invisible eye-tracking objects and their properties for receiving and updating data on different topics

# UPupilLabsVR
Plugin for connecting to Pupil Labs VR using the ZeroMQ and MsgPack library

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

Common Errors For Installing the eye-tracker:

Can't compile C++ : missing "alts.lib" - Solution : Open Visual Studio Installer -> Select Desktop development with c++ -> Select MFC and Atl Support + VC++ 2015.3v 140 toolset for desktop and install them
