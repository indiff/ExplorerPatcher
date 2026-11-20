#pragma once

typedef ULONGLONG RTL_FEATURE_CHANGE_STAMP;

typedef RTL_FEATURE_CHANGE_STAMP NTAPI RTL_QUERY_FEATURE_CONFIGURATION_CHANGE_STAMP();

typedef UINT RTL_FEATURE_ID;

typedef enum _RTL_FEATURE_CONFIGURATION_PRIORITY
{
	FeatureConfigurationPriorityImageDefault = 0,
	FeatureConfigurationPriorityEKB = 1,
	FeatureConfigurationPrioritySafeguard = 2,
	FeatureConfigurationPriorityPersistent = 2,
	FeatureConfigurationPriorityImageDefaultEditionOverride = 3,
	FeatureConfigurationPriorityService = 4,
	FeatureConfigurationPriorityReserved5 = 5,
	FeatureConfigurationPriorityDynamic = 6,
	FeatureConfigurationPriorityReserved7 = 7,
	FeatureConfigurationPriorityUser = 8,
	FeatureConfigurationPrioritySecurity = 9,
	FeatureConfigurationPriorityUserPolicy = 10,
	FeatureConfigurationPriorityReserved11 = 11,
	FeatureConfigurationPriorityTest = 12,
	FeatureConfigurationPriorityReserved13 = 13,
	FeatureConfigurationPriorityReserved14 = 14,
	FeatureConfigurationPriorityImageOverride = 15,
	FeatureConfigurationPriorityMax = 15,
} RTL_FEATURE_CONFIGURATION_PRIORITY, *PRTL_FEATURE_CONFIGURATION_PRIORITY;

typedef enum _RTL_FEATURE_ENABLED_STATE
{
	FeatureEnabledStateDefault = 0,
	FeatureEnabledStateDisabled = 1,
	FeatureEnabledStateEnabled = 2,
} RTL_FEATURE_ENABLED_STATE, *PRTL_FEATURE_ENABLED_STATE;

typedef enum _RTL_FEATURE_VARIANT_PAYLOAD_KIND
{
	FeatureVariantPayloadKindNone = 0,
	FeatureVariantPayloadKindResident = 1,
	FeatureVariantPayloadKindExternal = 2,
} RTL_FEATURE_VARIANT_PAYLOAD_KIND, *PRTL_FEATURE_VARIANT_PAYLOAD_KIND;

typedef UINT RTL_FEATURE_VARIANT_PAYLOAD;

typedef enum _RTL_FEATURE_CONFIGURATION_TYPE
{
	RtlFeatureConfigurationBoot = 0,
	RtlFeatureConfigurationRuntime = 1,
	RtlFeatureConfigurationCount = 2,
} RTL_FEATURE_CONFIGURATION_TYPE, *PRTL_FEATURE_CONFIGURATION_TYPE;

typedef struct _RTL_FEATURE_CONFIGURATION
{
	RTL_FEATURE_ID FeatureId;
	UINT Priority : 4; // RTL_FEATURE_CONFIGURATION_PRIORITY
	UINT EnabledState : 2; // RTL_FEATURE_ENABLED_STATE
	UINT IsWexpConfiguration : 1;
	UINT HasSubscriptions : 1;
	UINT Variant : 6;
	UINT VariantPayloadKind : 2; // RTL_FEATURE_VARIANT_PAYLOAD_KIND
	RTL_FEATURE_VARIANT_PAYLOAD VariantPayload;
} RTL_FEATURE_CONFIGURATION, *PRTL_FEATURE_CONFIGURATION;

typedef NTSTATUS NTAPI RTL_QUERY_FEATURE_CONFIGURATION(
	_In_ RTL_FEATURE_ID FeatureId,
	_In_ RTL_FEATURE_CONFIGURATION_TYPE ConfigurationType,
	_Out_ RTL_FEATURE_CHANGE_STAMP* ChangeStamp,
	_Out_ RTL_FEATURE_CONFIGURATION* FeatureConfiguration);

typedef void NTAPI RTL_FEATURE_CONFIGURATION_CHANGE_CALLBACK(PVOID Context);

typedef void* RTL_FEATURE_CONFIGURATION_CHANGE_REGISTRATION;

typedef NTSTATUS NTAPI RTL_REGISTER_FEATURE_CONFIGURATION_CHANGE_NOTIFICATION(
	_In_ RTL_FEATURE_CONFIGURATION_CHANGE_CALLBACK* Callback,
	_In_ PVOID Context,
	_In_opt_ RTL_FEATURE_CHANGE_STAMP* ObservedChangeStamp,
	_Out_ RTL_FEATURE_CONFIGURATION_CHANGE_REGISTRATION* RegistrationHandle);

typedef void NTAPI RTL_UNREGISTER_FEATURE_CONFIGURATION_CHANGE_NOTIFICATION(
	_In_ RTL_FEATURE_CONFIGURATION_CHANGE_REGISTRATION RegistrationHandle);

typedef enum _RTL_FEATURE_ENABLED_STATE_OPTIONS
{
	FeatureEnabledStateOptionsNone = 0,
	FeatureEnabledStateOptionsWexpConfig = 1,
} RTL_FEATURE_ENABLED_STATE_OPTIONS, *PRTL_FEATURE_ENABLED_STATE_OPTIONS;

typedef struct _RTL_FEATURE_USAGE_REPORT
{
	RTL_FEATURE_ID FeatureId;
	USHORT ReportingKind;
	USHORT ReportingOptions; // RTL_FEATURE_ENABLED_STATE_OPTIONS
} RTL_FEATURE_USAGE_REPORT, *PRTL_FEATURE_USAGE_REPORT;

typedef NTSTATUS NTAPI RTL_NOTIFY_FEATURE_USAGE(_In_ RTL_FEATURE_USAGE_REPORT* FeatureUsageReport);
