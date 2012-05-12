# - Find PMIniParser
# Copyright (C) 2012 Massimo Gengarelli <massimo.gengarelli@gmail.com>

FIND_PATH(PmIniParser_INCLUDE_DIR
    PM_IP_IniElement.h
    PM_IP_Parser.h)
    
FIND_LIBRARY(PmIniParser_LIBRARY
    PmIniParser)
    
IF(PmIniParser_INCLUDE_DIR AND PmIniParser_LIBRARY)
    MESSAGE(STATUS "Found PmIniParser: ${PmIniParser_LIBRARY}")
    SET(PmIniParser_FOUND TRUE)
ELSE()
    MESSAGE(STATUS "PmIniParser not found")
    SET(PmIniParser_FOUND FALSE)
ENDIF()
