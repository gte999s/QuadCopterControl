  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (sensorTask_P)
    ;%
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% sensorTask_P.WrapToZero_Threshold
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% sensorTask_P.Constant_Value
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% sensorTask_P.FixPtConstant_Value
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% sensorTask_P.Output_InitialCondition
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (sensorTask_B)
    ;%
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% sensorTask_B.TmpSignalConversionAtUDPSendInp
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o1
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 32;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o2
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 36;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o3
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 40;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o4
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 44;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o5
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 48;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o6
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 52;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o7
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 56;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o8
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 58;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o9
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 60;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o10
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 62;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 1;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (sensorTask_DW)
    ;%
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% sensorTask_DW.readAccelGyroMagSfun_DSTATE
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% sensorTask_DW.UDPSend_NetworkLib
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% sensorTask_DW.Output_DSTATE
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 2104941394;
  targMap.checksum1 = 2543980290;
  targMap.checksum2 = 3143385757;
  targMap.checksum3 = 3014307242;

