##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=aorServer
ConfigurationName      :=Debug
WorkspacePath          := "/home/razool/Documents/LogMeIn"
ProjectPath            := "/home/razool/Documents/LogMeIn/aorServer"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Dany Chateauneuf
Date                   :=19/02/19
CodeLitePath           :="/home/razool/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="aorServer.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/source_main.c$(ObjectSuffix) $(IntermediateDirectory)/server_serverInit.c$(ObjectSuffix) $(IntermediateDirectory)/server_serverJson.c$(ObjectSuffix) $(IntermediateDirectory)/server_serverTerminate.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/source_main.c$(ObjectSuffix): source/main.c $(IntermediateDirectory)/source_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/LogMeIn/aorServer/source/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_main.c$(DependSuffix): source/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/source_main.c$(DependSuffix) -MM "source/main.c"

$(IntermediateDirectory)/source_main.c$(PreprocessSuffix): source/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_main.c$(PreprocessSuffix) "source/main.c"

$(IntermediateDirectory)/server_serverInit.c$(ObjectSuffix): source/server/serverInit.c $(IntermediateDirectory)/server_serverInit.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/LogMeIn/aorServer/source/server/serverInit.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server_serverInit.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server_serverInit.c$(DependSuffix): source/server/serverInit.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server_serverInit.c$(ObjectSuffix) -MF$(IntermediateDirectory)/server_serverInit.c$(DependSuffix) -MM "source/server/serverInit.c"

$(IntermediateDirectory)/server_serverInit.c$(PreprocessSuffix): source/server/serverInit.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server_serverInit.c$(PreprocessSuffix) "source/server/serverInit.c"

$(IntermediateDirectory)/server_serverJson.c$(ObjectSuffix): source/server/serverJson.c $(IntermediateDirectory)/server_serverJson.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/LogMeIn/aorServer/source/server/serverJson.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server_serverJson.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server_serverJson.c$(DependSuffix): source/server/serverJson.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server_serverJson.c$(ObjectSuffix) -MF$(IntermediateDirectory)/server_serverJson.c$(DependSuffix) -MM "source/server/serverJson.c"

$(IntermediateDirectory)/server_serverJson.c$(PreprocessSuffix): source/server/serverJson.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server_serverJson.c$(PreprocessSuffix) "source/server/serverJson.c"

$(IntermediateDirectory)/server_serverTerminate.c$(ObjectSuffix): source/server/serverTerminate.c $(IntermediateDirectory)/server_serverTerminate.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/LogMeIn/aorServer/source/server/serverTerminate.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server_serverTerminate.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server_serverTerminate.c$(DependSuffix): source/server/serverTerminate.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server_serverTerminate.c$(ObjectSuffix) -MF$(IntermediateDirectory)/server_serverTerminate.c$(DependSuffix) -MM "source/server/serverTerminate.c"

$(IntermediateDirectory)/server_serverTerminate.c$(PreprocessSuffix): source/server/serverTerminate.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server_serverTerminate.c$(PreprocessSuffix) "source/server/serverTerminate.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


