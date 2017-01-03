  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 0;
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
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (sensorTask_P)
    ;%
    
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
	  section.data(2).dtTransOffset = 31;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o2
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 35;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o3
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 39;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o4
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 43;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o5
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 47;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o6
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 51;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o7
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 55;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o8
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 57;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o9
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 59;
	
	  ;% sensorTask_B.readAccelGyroMagSfun_o10
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 61;
	
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
    nTotSects     = 1;
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


  targMap.checksum0 = 3935354751;
  targMap.checksum1 = 1656119003;
  targMap.checksum2 = 818636135;
  targMap.checksum3 = 2569935220;

