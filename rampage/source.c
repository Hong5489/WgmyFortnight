int entry(void)

{
  code *pcVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  code **ppcVar5;
  uint *puVar6;
  int _Code;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined *this;
  undefined4 uVar9;
  int local_24;
  undefined4 local_14;
  
  FUN_004015e5();
  uVar3 = ___scrt_initialize_crt(1);
  if ((char)uVar3 != 0) {
    bVar2 = false;
    uVar3 = FUN_0040138b();
    if (DAT_0041b900 != 1) {
      if (DAT_0041b900 == 0) {
        DAT_0041b900 = 1;
        this = &DAT_0041413c;
        iVar4 = __initterm_e((undefined **)&DAT_00414124,(undefined **)&DAT_0041413c);
        if (iVar4 != 0) {
          _Code = 0xff;
          goto LAB_00401317;
        }
        __initterm(this,(undefined **)&DAT_00414118,(undefined **)&DAT_00414120);
        DAT_0041b900 = 2;
      }
      else {
        bVar2 = true;
      }
      ___scrt_release_startup_lock((char)uVar3);
      ppcVar5 = (code **)FUN_0040169d();
      if (*ppcVar5 != (code *)0x0) {
        uVar3 = FUN_0040147d((int)ppcVar5);
        if ((char)uVar3 != 0) {
          pcVar1 = *ppcVar5;
          uVar9 = 0;
          uVar8 = 2;
          uVar7 = 0;
          _guard_check_icall();
          (*pcVar1)(uVar7,uVar8,uVar9);
        }
      }
      puVar6 = (uint *)FUN_004016a3();
      if (*puVar6 != 0) {
        uVar3 = FUN_0040147d((int)puVar6);
        if ((char)uVar3 != 0) {
          __register_thread_local_exe_atexit_callback(*puVar6);
        }
      }
      FUN_00405960();
      FUN_00405e1f();
      FUN_00405e19();
      _Code = FUN_00401040();
      uVar3 = FUN_004017c8();
      if ((char)uVar3 != 0) {
        if (!bVar2) {
          __cexit();
        }
        ___scrt_uninitialize_crt(1,0);
LAB_00401317:
        *in_FS_OFFSET = local_14;
        return _Code;
      }
      goto LAB_0040132e;
    }
  }
  FUN_004016a9(7);
LAB_0040132e:
  _exit(_Code);
  __exit(local_24);
  pcVar1 = (code *)swi(3);
  iVar4 = (*pcVar1)();
  return iVar4;
}

undefined4 FUN_00401040(void)

{
  FILE *_File;
  uint _MaxCount;
  uint uVar1;
  byte local_10 [12];
  
  _File = _fopen(&DAT_0041b8f8,&DAT_0041b8fc);
  if (_File != (FILE *)0x0) {
    _fseek(_File,0,2);
    _MaxCount = _ftell(_File);
    _fseek(_File,0,0);
    FUN_00401010((int)&DAT_0041b8d8);
    GetCurrentProcessId();
    FUN_00401010((int)s_Current_PID:_%d_0041b8c4);
    FUN_00401010((int)&DAT_0041b8c0);
    _fgets((char *)local_10,_MaxCount,_File);
    uVar1 = 0;
    _DAT_0041c320 = 0;
    if (_MaxCount != 0) {
      do {
        local_10[uVar1] = local_10[uVar1] ^ 0xcc;
        uVar1 = uVar1 + 1;
        _DAT_0041c320 = uVar1;
      } while (uVar1 < _MaxCount);
    }
    FUN_00401010((int)s_Good_luck..._0041b8b0);
    return 0;
  }
  FUN_00401010((int)s__Error_opening_file_`buf`_0041b8dc);
  return 1;
}
