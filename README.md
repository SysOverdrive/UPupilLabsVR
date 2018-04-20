# UPupilLabsVR
Plugin for connecting to Pupil Labs VR using the ZeroMQ library

<b>Installation</b>
<br/>1.Download this in to the ..\Plugins folder of your Project
<br/>2.In Project.build.cs file add "UPupilLabsVR" in the PublicDependecyModulesNames

For the Moment all info is logged in the console.
The relevant Fstring Variables are:
   <br/>topicRequest
   <br/>infoRequest

One can subscribe to different topics using 
     <br/>string filter = u8"";
  <br/>	//string filter = u8"gaze";
  <br/>	//string filter = u8"notify";
  <br/>	//string filter = u8"pupil";
  <br/>	//string filter = u8"logging";
  
  Currently uses port 55555 on localhost

Common Errors:

Can't compile C++ : missing "alts.lib" - Solution : Configuration Manager -> UE4 Platform -> Select X64
