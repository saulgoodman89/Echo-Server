
#[[
	SET(<변수명> <값>)
    	
    	변수참조는 $변수명 
	${<변수명>}  으로 한다. 
]]

SET ( SERVER_SRC_FILES server.c)
ADD_EXECUTABLE(Server ${SERVER_SRC_FILES})
ADD_EXECUTABLE(Client client.c)


#[[ 
	CMAKE_MINIMUM_REQUIRED : 필요 CMake 최소 버전 명시 
	CMAKE_MINIMUM_REQUIRED (VERSION <버전>)
    	CMAKE_MINIMUM_REQUIRED (VERSION 2.8) 

]]
