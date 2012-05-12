# - Find PhantomMenace
# Copyright (C) 2012 Massimo Gengarelli <massimo.gengarelli@gmail.com>

FIND_PATH(PhantomMenace_INCLUDE_DIR
    PM_Element.h
    PM_GrammarElement.h
    PM_ParsingEnvironment.h
    PM_Validator.h)
    
FIND_LIBRARY(PhantomMenace_LIBRARY
    PhantomMenace)
    
IF(PhantomMenace_INCLUDE_DIR AND PhantomMenace_LIBRARY)
    MESSAGE(STATUS "Found PhantomMenace: ${PhantomMenace_LIBRARY}")
    SET(PhantomMenace_FOUND TRUE)
ELSE()
    MESSAGE(STATUS "PhantomMenace not found")
    SET(PhantomMenace_FOUND FALSE)
ENDIF()
