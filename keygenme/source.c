
void main(void)

{
  code *pcVar1;
  FILE *stdin;
  size_t sVar2;
  uint uVar3;
  char *pcVar4;
  undefined uVar5;
  undefined uVar6;
  char cVar7;
  undefined4 uStack36;
  undefined4 uStack32;
  undefined4 uStack28;
  undefined8 local_18;
  undefined4 local_10;
  undefined2 local_c;
  uint local_8;
  
  local_8 = DAT_00403004 ^ (uint)&stack0xfffffffc;
  local_10 = 0;
  uVar5 = 0x1c;
  cVar7 = 0;
  uStack36 = 0;
  uStack32 = 0;
  uStack28 = 0;
  local_c = 0;
  local_18 = 0;
  printf("                             ________              .__ \n",0);
  uVar6 = 0x58;
  printf("__  _  ______   _____ ___.__.\\_____  \\ __ __  ____ |__|\n",uVar5);
  uVar5 = 0x94;
  printf("\\ \\/ \\/ / ___\\ /     <   |  | /  ____/|  |  \\/    \\|  |\n",uVar6);
  uVar6 = 0xd0;
  printf(" \\     / /_/  >  Y Y  \\___  |/       \\|  |  /   |  \\  |\n",uVar5);
  uVar5 = 0xc;
  printf("  \\/\\_/\\___  /|__|_|  / ____|\\_______ \\____/|___|  /__|\n",uVar6);
  uVar6 = 0x48;
  printf("      /_____/       \\/\\/             \\/          \\/    \n",uVar5);
  uVar5 = 0x84;
  printf("keygenme - wgmy2uni\n",uVar6);
  printf("serial: ",uVar5);
  stdin = (FILE *)__acrt_iob_func(0);
  fgets(&stack0xffffffd8,0x1e,stdin);
  sVar2 = strcspn(&stack0xffffffd8,"\n");
  if (sVar2 < 0x1e) {
    (&stack0xffffffd8)[sVar2] = 0;
    uVar3 = FUN_00401000(&stack0xffffffd8);
    pcVar4 = "congratz!\n";
    if (uVar3 != 1) {
      pcVar4 = "nope!\n";
    }
    printf(pcVar4,cVar7);
    FUN_00401270();
    return;
  }
  ___report_rangecheckfailure();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

uint __fastcall FUN_00401000(char *param_1)

{
  char *pcVar4;
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  undefined4 local_6c;
  undefined4 uStack104;
  undefined4 uStack100;
  undefined4 uStack96;
  undefined4 local_5c;
  undefined4 uStack88;
  undefined4 uStack84;
  undefined4 uStack80;
  undefined4 local_4c;
  undefined4 uStack72;
  undefined4 uStack68;
  undefined4 uStack64;
  undefined4 local_3c;
  undefined4 uStack56;
  undefined4 uStack52;
  undefined4 uStack48;
  undefined4 local_2c;
  undefined4 uStack40;
  undefined4 uStack36;
  undefined4 uStack32;
  undefined4 local_1c;
  undefined4 uStack24;
  undefined4 uStack20;
  undefined4 uStack16;
  undefined4 local_c;
  undefined4 local_8;
  char cVar1;
  char cVar2;
  int iVar3;
  
  local_6c = 1;
  uStack104 = 0;
  uStack100 = 0;
  uStack96 = 0;
  iVar4 = 1;
  local_5c = 4;
  uStack88 = 0;
  uStack84 = 0xffffff7c;
  uStack80 = 0;
  local_c = 0x539;
  local_8 = 0;
  local_4c = 0;
  uStack72 = 0;
  uStack68 = 0;
  uStack64 = 0;
  local_3c = 0xfffffff9;
  uStack56 = 0;
  uStack52 = 0;
  uStack48 = 0;
  local_2c = 0;
  uStack40 = 0x22c4;
  uStack36 = 3;
  uStack32 = 0;
  local_1c = 0;
  uStack24 = 0;
  uStack20 = 0xffffffec;
  uStack16 = 0;
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != 0);
  if ((pcVar3 + -(int)(param_1 + 1) == (char *)0x13) &&
     (pcVar4 = strchr(param_1,0x2d), pcVar4 != (char *)0x0)) {
    do {
      pcVar4 = strchr(pcVar4 + 1,0x2d);
      iVar4 = iVar4 + 1;
    } while (pcVar4 != (char *)0x0);
    if (iVar4 == 4) {
      pcVar1 = strtok(param_1,"-");
      do {
        if (pcVar1 == (char *)0x0) {
          return (uint)(iVar4 == 8);
        }
        iVar5 = 0;
        do {
          iVar2 = isalnum((int)pcVar1[iVar5]);
          if (iVar2 == 0) {
            return 0;
          }
          cVar2 = pcVar1[iVar5];
          if (('`' < cVar2) && (cVar2 < '{')) {
            return 0;
          }
          if (('/' < cVar2) && (cVar2 < ':')) {
            return 0;
          }
          iVar3 = *(int *)(&stack0xfffffe90 + (int)cVar2 * 4);
          *(int *)(&stack0xfffffe90 + (int)cVar2 * 4) = iVar3 + 1;
          if (iVar3 != 0) {
            return 0;
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < 4);
        pcVar1 = strtok((char *)0x0,"-");
        iVar4 = iVar4 + 1;
      } while( true );
    }
  }
  return 0;
}
