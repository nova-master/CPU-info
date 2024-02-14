#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Register/Cpuid.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>
#include <Library/FileHandleLib.h>
#include <Library/DevicePathLib.h>
#include <Library/BaseMemoryLib.h> 
#include <Guid/SmBios.h>
#include <Protocol/Smbios.h>
#include <Library/DebugLib.h>

EFI_STATUS
PrintCpuVersionInfo()
{
  CPUID_VERSION_INFO_EAX VersionInfo;

  // Execute CPUID instruction to retrieve version information
  AsmCpuidEx(1, 0, &VersionInfo.Uint32, NULL, NULL, NULL);

  // Print CPU version information
  Print(L"CPU Version Information:\n");
  Print(L"Stepping ID: %d\n", VersionInfo.Bits.SteppingId);
  Print(L"Model: %d\n", VersionInfo.Bits.Model);
  Print(L"Family ID: %d\n", VersionInfo.Bits.FamilyId);
  Print(L"Processor Type: %d\n", VersionInfo.Bits.ProcessorType);
  Print(L"Extended Model ID: %d\n", VersionInfo.Bits.ExtendedModelId);
  Print(L"Extended Family ID: %d\n", VersionInfo.Bits.ExtendedFamilyId);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UefiMain(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
)
{
  

  // Print CPU version information
  EFI_STATUS Status = PrintCpuVersionInfo();
  gBS->Stall(15000000);
  if (EFI_ERROR(Status)) {
    Print(L"Failed to print CPU version information: %r\n", Status);
    gBS->Stall(5000000);
  }

  return Status;
}
