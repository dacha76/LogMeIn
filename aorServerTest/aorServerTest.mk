##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=aorServerTest
ConfigurationName      :=Debug
WorkspacePath          := "/home/razool/Documents/GitHub/LogMeIn"
ProjectPath            := "/home/razool/Documents/GitHub/LogMeIn/aorServerTest"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Dany Chateauneuf
Date                   :=21/02/19
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
ObjectsFileList        :="aorServerTest.txt"
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
Objects0=$(IntermediateDirectory)/source_main.c$(ObjectSuffix) $(IntermediateDirectory)/tests_test_0.c$(ObjectSuffix) $(IntermediateDirectory)/tests_test_1.c$(ObjectSuffix) $(IntermediateDirectory)/client_client.c$(ObjectSuffix) $(IntermediateDirectory)/client_client_socket.c$(ObjectSuffix) 



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
	$(CC) $(SourceSwitch) "/home/razool/Documents/GitHub/LogMeIn/aorServerTest/source/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_main.c$(DependSuffix): source/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/source_main.c$(DependSuffix) -MM "source/main.c"

$(IntermediateDirectory)/source_main.c$(PreprocessSuffix): source/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_main.c$(PreprocessSuffix) "source/main.c"

$(IntermediateDirectory)/tests_test_0.c$(ObjectSuffix): source/tests/test_0.c $(IntermediateDirectory)/tests_test_0.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/GitHub/LogMeIn/aorServerTest/source/tests/test_0.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tests_test_0.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_test_0.c$(DependSuffix): source/tests/test_0.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_test_0.c$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_test_0.c$(DependSuffix) -MM "source/tests/test_0.c"

$(IntermediateDirectory)/tests_test_0.c$(PreprocessSuffix): source/tests/test_0.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_test_0.c$(PreprocessSuffix) "source/tests/test_0.c"

$(IntermediateDirectory)/tests_test_1.c$(ObjectSuffix): source/tests/test_1.c $(IntermediateDirectory)/tests_test_1.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/GitHub/LogMeIn/aorServerTest/source/tests/test_1.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tests_test_1.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_test_1.c$(DependSuffix): source/tests/test_1.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_test_1.c$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_test_1.c$(DependSuffix) -MM "source/tests/test_1.c"

$(IntermediateDirectory)/tests_test_1.c$(PreprocessSuffix): source/tests/test_1.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_test_1.c$(PreprocessSuffix) "source/tests/test_1.c"

$(IntermediateDirectory)/client_client.c$(ObjectSuffix): source/client/client.c $(IntermediateDirectory)/client_client.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/GitHub/LogMeIn/aorServerTest/source/client/client.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/client_client.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/client_client.c$(DependSuffix): source/client/client.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/client_client.c$(ObjectSuffix) -MF$(IntermediateDirectory)/client_client.c$(DependSuffix) -MM "source/client/client.c"

$(IntermediateDirectory)/client_client.c$(PreprocessSuffix): source/client/client.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/client_client.c$(PreprocessSuffix) "source/client/client.c"

$(IntermediateDirectory)/client_client_socket.c$(ObjectSuffix): source/client/client_socket.c $(IntermediateDirectory)/client_client_socket.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/razool/Documents/GitHub/LogMeIn/aorServerTest/source/client/client_socket.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/client_client_socket.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/client_client_socket.c$(DependSuffix): source/client/client_socket.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/client_client_socket.c$(ObjectSuffix) -MF$(IntermediateDirectory)/client_client_socket.c$(DependSuffix) -MM "source/client/client_socket.c"

$(IntermediateDirectory)/client_client_socket.c$(PreprocessSuffix): source/client/client_socket.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/client_client_socket.c$(PreprocessSuffix) "source/client/client_socket.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


