CmdDesktopSwitch
================
CmdDesktopSwitch is a small utility that lists all windows desktops assigned to the window station that the default desktop is assigned to. CmdDesktopSwitch then provides the option to switch to one of the enumerated desktops.

This can be used to identify and watch malware that has created a hidden desktop in order to hide a window. More details can be found [here](http://herrcore.blogspot.com/). 

##How Robust Is This Tool?
This tool was mainly developed to be used in the lab not during live response. The tool operates in user land and calls the windows API so it is vulnerable to all the usual hooking techniques used to hide malware. It also only enumerates desktops on the window station that the default desktop is assigned to. The tool can certainly be used during live response but due these limitations it should only be used to prove a positive (ie. there is malware) and never relied on to prove a negative (ie. there is no malware). 

##Why Use This Tool?
Volatility deskscan does a much more thorough job of enumerating desktops however if a memory dump is not available and live response is required the tool could be used in a pinch. Where it really excels though is watching malware operate. This is especially true in the case of ad-fraud malware where the malware has opened a browser on a hidden desktop and is using the browser to defraud advertisers. By using this tool you can actually see what the malware is doing, what ads it is loading, etc.

