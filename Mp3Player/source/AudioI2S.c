#include "Audio.h"

#if AUDIO_OUTPUT == I2S

#include "fsl_sai_edma.h"
#include "fsl_dmamux.h"
#include "assert.h"

#define  AUDIO_BUFFER_SIZE 2304
#undef 	SAI_XFER_QUEUE_SIZE
#define  CIRC_BUFFER_LEN 2
#define SAI_XFER_QUEUE_SIZE CIRC_BUFFER_LEN


#define AUDIO_SAI 			I2S0
#define AUDIO_DMA 			DMA0
#define AUDIO_DMA_CHANNEL	0
#define SAI_TX_DMA_REQUEST  kDmaRequestMux0I2S0Tx

#define AUDIO_DMA_IRQ_ID DMA0_IRQn

typedef struct{
	uint16_t samples[AUDIO_BUFFER_SIZE];
	uint16_t nSamples;
	uint32_t sampleRate;
	uint32_t frameNumber;
}PCM_AudioFrame;

static PCM_AudioFrame audioFrame[CIRC_BUFFER_LEN+1];


static void EDMA_Configuration(void);

static void DMAMUX_Configuration(void);


static void SAI_Configuration(void);


static void SAI_Callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData);

static edma_handle_t DMA_Handle;             /* Edma DMA_Handler */
static sai_edma_handle_t SAI_Handle;
static sai_transfer_format_t SAI_TransferFormat;




status_t Audio_Init()
{
	/* Initialize DMAMUX. */
	DMAMUX_Configuration();

	/* Initialize EDMA. */
	EDMA_Configuration();

	/* Initialize DAC. */
	SAI_Configuration();

	return kStatus_Success;

}

void Audio_ResetBuffers()
{
	for(int i=0; i<CIRC_BUFFER_LEN; i++)
	{
		memset(audioFrame[i].samples,0,AUDIO_BUFFER_SIZE);
		audioFrame[i].nSamples = AUDIO_BUFFER_SIZE;
		audioFrame[i].sampleRate = 44100;
	}
}

void Audio_Play()
{
	/* Enable Tx */
	SAI_TxEnable(AUDIO_SAI, true);

	/* Enable DMA */
	SAI_TxEnableDMA(AUDIO_SAI, kSAI_FIFORequestDMAEnable, true);
}

void Audio_Stop()
{
	SAI_TransferTerminateReceiveEDMA(AUDIO_SAI, &SAI_Handle);
	Audio_ResetBuffers();
}

void Audio_Pause()
{
	SAI_TransferAbortSendEDMA(AUDIO_SAI, &SAI_Handle);
}

void Audio_Resume()
{
	/* Enable Tx */
	SAI_TxEnable(AUDIO_SAI, true);

	/* Enable DMA */
	SAI_TxEnableDMA(AUDIO_SAI, kSAI_FIFORequestDMAEnable, true);


}
uint16_t * Audio_GetBackBuffer()
{
	return audioFrame[DMA_Handle.tail].samples;
}


uint32_t Audio_GetCurrentFrameNumber()
{
	NVIC_DisableIRQ(AUDIO_DMA_IRQ_ID);
	uint32_t n = audioFrame[DMA_Handle.header].frameNumber;
	NVIC_EnableIRQ(AUDIO_DMA_IRQ_ID);
	return n;
}

void Audio_FillBackBuffer(int16_t* samples, uint16_t nSamples, uint32_t sampleRate, uint32_t frameNumber)
{
	// Average stereo channels
	for(int i=0; i<nSamples; i++)
	{
		audioFrame[DMA_Handle.tail].samples[i] = ((uint16_t)(samples[i]+32768))>>4;
	}

	audioFrame[DMA_Handle.tail].nSamples = nSamples/2;
	audioFrame[DMA_Handle.tail].sampleRate = sampleRate;
	audioFrame[DMA_Handle.tail].frameNumber = frameNumber;

	sai_transfer_t transfer = {.data = (uint8_t*)audioFrame[DMA_Handle.tail].samples, .dataSize = 2*nSamples};

	status_t s = SAI_TransferSendEDMA(AUDIO_SAI,&SAI_Handle,&transfer);

	assert(s==kStatus_Success);
}

void Audio_SetSampleRate(uint32_t sr)
{
	SAI_TransferFormat.sampleRate_Hz = sr;

	SAI_TxSetFormat(AUDIO_SAI,&SAI_TransferFormat,0000,0000);

}

bool Audio_BackBufferIsFree()
{
	NVIC_DisableIRQ(AUDIO_DMA_IRQ_ID);
	bool b = (DMA_Handle.tail+1)%DMA_Handle.tcdSize != DMA_Handle.header;
	NVIC_EnableIRQ(AUDIO_DMA_IRQ_ID);
	return b;
}

bool Audio_BackBufferIsEmpty()
{
	NVIC_DisableIRQ(AUDIO_DMA_IRQ_ID);
	bool b = (DMA_Handle.tcdUsed == 0);
	NVIC_EnableIRQ(AUDIO_DMA_IRQ_ID);
	return b;
}


static void SAI_Callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{
	Audio_SetSampleRate(audioFrame[DMA_Handle.header].sampleRate);
}

static void EDMA_Configuration(void)
{

    edma_config_t userConfig;
    EDMA_GetDefaultConfig(&userConfig);

    userConfig.enableRoundRobinArbitration = false;
    userConfig.enableHaltOnError = true;
    userConfig.enableContinuousLinkMode = false;
    userConfig.enableDebugMode = true;

    EDMA_Init(AUDIO_DMA, &userConfig);

	/* Creates the DMA handle. */
	EDMA_CreateHandle(&DMA_Handle, AUDIO_DMA, AUDIO_DMA_CHANNEL);
}

static void DMAMUX_Configuration(void)
{
	// Sets up the DMA.
	DMAMUX_Init(DMAMUX0);

	DMAMUX_SetSource(DMAMUX0, AUDIO_DMA_CHANNEL, SAI_TX_DMA_REQUEST);

	DMAMUX_EnableChannel(DMAMUX0, AUDIO_DMA_CHANNEL);
}


static void SAI_Configuration(void)
{
	sai_config_t config;

	SAI_TxGetDefaultConfig(&config);

	SAI_TxInit(AUDIO_SAI, &config);

	SAI_TxEnable(AUDIO_SAI, true);

	SAI_TransferTxCreateHandleEDMA(AUDIO_SAI, &SAI_Handle, SAI_Callback, NULL, &DMA_Handle);
}


#endif
