# Unity Demo
A simple Unity package for use with the JunoVR respiration sensor. The overall design was inspired by and adapted from [DWilches/SerialCommUnity](https://github.com/DWilches/SerialCommUnity).

## How to use
This directory contains both the raw project code as well as a compiled Unity package. Feel free to browse the raw files, but for actual use please download the Unity package inside the CompiledPackage directory. To import a package within Unity, select Assets > Import Package > Custom Package.

After the package is imported into your project, you should see the new folder /Assets/breathwith. After that, simply find and drag the `BreatheWith` prefab into your scene! Refer to the `sphere` scene for a sample of how this works.

## Troubleshooting
Make sure your Unity project supports COM port communication. The option at Edit > Project Settings > Player > Other Settings > Api Compatibility Level should be set to ".Net 2.0".