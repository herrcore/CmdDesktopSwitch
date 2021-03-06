CmdDesktopSwitch
================
CmdDesktopSwitch is a small utility that lists all windows desktops assigned to the window station that the default desktop is assigned to. CmdDesktopSwitch then provides the option to switch to one of the enumerated desktops.

This can be used to identify and watch malware that has created a hidden desktop in order to hide a window. More details can be found [here](http://herrcore.blogspot.com/2014/11/exposing-malware-in-hidden-desktops.html). 

##How Robust Is This Tool?
This tool was mainly developed to be used in the lab not during live response. The tool operates in user land and calls the windows API so it is vulnerable to all the usual hooking techniques used to hide malware. It also only enumerates desktops on the window station that the default desktop is assigned to. The tool can certainly be used during live response but due these limitations it should only be used to prove a positive (ie. there is malware) and never relied on to prove a negative (ie. there is no malware). 

##Why Use This Tool?
Volatility does a much more thorough job of enumerating desktops however if a memory dump is not available and live response is required the tool could be used. Where it really excels though is during malware analysis. You can use the tool to visually watch malware operate. This is especially useful in the case of ad-fraud malware where the malware has opened a browser on a hidden desktop and is using the browser to defraud advertisers. By using this tool you can actually see what the malware is doing, what ads it is loading, etc.
