##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=aorServer
ConfigurationName      :=Debug
WorkspacePath          := "/home/razool/Documents/GitHub/LogMeIn"
ProjectPath            := "/home/razool/Documents/GitHub/LogMeIn/aorServer"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Dany Chateauneuf
Date                   :=20/02/19
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
Objects0=$(IntermediateDirectory)/source_main.c$(ObjectSuffix) $(IntermediateDirectory)/server_server_cnct.c$(ObjectSuffix) $(IntermediateDirectory)/server_server.c$(ObjectSuffix) $(IntermediateDirectory)/server_server_Json.c$(ObjectSuffix) $(IntermediateDirectory)/server_server_socket.c$(ObjectSuffix) 



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
	$(CC) $(SourceSwitch) "/home/razool/Documents/GitHub/LogMeIn/aorServer/source/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_main.c$(DependSuffix): source/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/source_main.c$(DependSuffix) -MM "source/main.c"

$(IntermediateDirectory)/source_main.c$(PreprocessSuffix): source/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_main.c$(PreprocessSuffix) "source/main.c"

$(IntermediateDirectory)/server_server_cnct.c$(ObjectSuffix): source/server/server_cnct.c $(IntermediateDirectory)/server_server_cnct.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/GitHub/LogMeIn/aorServer/source/server/server_cnct.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server_server_cnct.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server_server_cnct.c$(DependSuffix): source/server/server_cnct.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server_server_cnct.c$(ObjectSuffix) -MF$(IntermediateDirectory)/server_server_cnct.c$(DependSuffix) -MM "source/server/server_cnct.c"

$(IntermediateDirectory)/server_server_cnct.c$(PreprocessSuffix): source/server/server_cnct.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server_server_cnct.c$(PreprocessSuffix) "source/server/server_cnct.c"

$(IntermediateDirectory)/server_server.c$(ObjectSuffix): source/server/server.c $(IntermediateDirectory)/server_server.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/GitHub/LogMeIn/aorServer/source/server/server.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server_server.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server_server.c$(DependSuffix): source/server/server.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server_server.c$(ObjectSuffix) -MF$(IntermediateDirectory)/server_server.c$(DependSuffix) -MM "source/server/server.c"

$(IntermediateDirectory)/server_server.c$(PreprocessSuffix): source/server/server.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server_server.c$(PreprocessSuffix) "source/server/server.c"

$(IntermediateDirectory)/server_server_Json.c$(ObjectSuffix): source/server/server_Json.c $(IntermediateDirectory)/server_server_Json.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/GitHub/LogMeIn/aorServer/source/server/server_Json.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server_server_Json.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server_server_Json.c$(DependSuffix): source/server/server_Json.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server_server_Json.c$(ObjectSuffix) -MF$(IntermediateDirectory)/server_server_Json.c$(DependSuffix) -MM "source/server/server_Json.c"

$(IntermediateDirectory)/server_server_Json.c$(PreprocessSuffix): source/server/server_Json.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server_server_Json.c$(PreprocessSuffix) "source/server/server_Json.c"

$(IntermediateDirectory)/server_server_socket.c$(ObjectSuffix): source/server/server_socket.c $(IntermediateDirectory)/server_server_socket.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/GitHub/LogMeIn/aorServer/source/server/server_socket.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server_server_socket.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server_server_socket.c$(DependSuffix): source/server/server_socket.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server_server_socket.c$(ObjectSuffix) -MF$(IntermediateDirectory)/server_server_socket.c$(DependSuffix) -MM "source/server/server_socket.c"

$(IntermediateDirectory)/server_server_socket.c$(PreprocessSuffix): source/server/server_socket.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server_server_socket.c$(PreprocessSuffix) "source/server/server_socket.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


