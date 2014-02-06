@echo off
echo Checking out project and filters file
p4 edit CcpMath.vcxproj
p4 edit CcpMath.vcxproj.filters
p4 edit CcpMath.v110_xp.vcxproj
p4 edit CcpMath.v110_xp.vcxproj.filters
p4 edit CcpMath.orbis.vcxproj
p4 edit CcpMath.orbis.vcxproj.filters
echo Regenerating
..\..\..\..\..\..\shared_tools\python\27\python.exe ..\..\tools\ProjectFileGenerator\ProjectFileGenerator.py -i CcpMath.ccpproj --toolset=v100
..\..\..\..\..\..\shared_tools\python\27\python.exe ..\..\tools\ProjectFileGenerator\ProjectFileGenerator.py -i CcpMath.ccpproj --toolset=v110_xp
..\..\..\..\..\..\shared_tools\python\27\python.exe ..\..\tools\ProjectFileGenerator\ProjectFileGenerator.py -i CcpMath.ccpproj --orbis
pause