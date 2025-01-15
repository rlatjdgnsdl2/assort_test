#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "Mesh.h"
#include "EngineBlend.h"
#include "EngineShader.h"
#include "EngineMaterial.h"
#include "EngineTexture.h"
#include "EngineFont.h"
#include "EngineDepthStencilState.h"


void UEngineGraphicDevice::DefaultResourcesInit()
{
	DepthStencilInit();
	TextureInit();
	MeshInit();
	BlendInit();
	RasterizerStateInit();
	ShaderInit();
	MaterialInit();

	UEngineFont::Load("궁서", "궁서");
}

void UEngineGraphicDevice::DepthStencilInit()
{
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("BaseDepth", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = false;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("UIDepth", Desc);
	}


	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("CollisionDebugDepth", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("TargetMerge", Desc);
	}

}

void UEngineGraphicDevice::TextureInit()
{

	D3D11_SAMPLER_DESC SampInfo = { D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT };
	SampInfo.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP; 		SampInfo.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP; 		SampInfo.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
	SampInfo.BorderColor[0] = 0.0f;
	SampInfo.BorderColor[1] = 0.0f;
	SampInfo.BorderColor[2] = 0.0f;
	SampInfo.BorderColor[3] = 0.0f;


	UEngineSampler::Create("WRAPSampler", SampInfo);


	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("EngineShader"))
		{
			MSGASSERT("EngineShader 폴더를 찾지 못했습니다.");
			return;
		}
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}
}

void UEngineGraphicDevice::ShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");

	std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

	for (size_t i = 0; i < ShaderFiles.size(); i++)
	{
		UEngineShader::ReflectionCompile(ShaderFiles[i]);
	}
}



void UEngineGraphicDevice::MeshInit()
{
	int a = 0;

	{
		std::vector<FEngineVertex> Vertexs;
		Vertexs.resize(4);
		Vertexs[0] = FEngineVertex{ FVector(-0.5f, 0.5f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[1] = FEngineVertex{ FVector(0.5f, 0.5f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[2] = FEngineVertex{ FVector(-0.5f, -0.5f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[3] = FEngineVertex{ FVector(0.5f, -0.5f, 0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };

		UEngineVertexBuffer::Create("Rect", Vertexs);
	}

	{
		std::vector<unsigned int> Indexs;

		Indexs.push_back(0);
		Indexs.push_back(1);
		Indexs.push_back(2);

		Indexs.push_back(1);
		Indexs.push_back(3);
		Indexs.push_back(2);
		UEngineIndexBuffer::Create("Rect", Indexs);
	}

	{
		std::vector<FEngineVertex> Vertexs;
		Vertexs.resize(4);
		Vertexs[0] = FEngineVertex{ FVector(-1.0f, 1.0f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[1] = FEngineVertex{ FVector(1.0f, 1.0f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[2] = FEngineVertex{ FVector(-1.0f, -1.0f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[3] = FEngineVertex{ FVector(1.0f, -1.0f, 0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };

		UEngineVertexBuffer::Create("FullRect", Vertexs);
	}

	{
		UMesh::Create("Rect");
		UMesh::Create("FullRect", "FullRect", "Rect");
	}

	{
		std::vector<FEngineVertex> Vertexs;
		Vertexs.resize(24);

		Vertexs[0] = FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.5f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[1] = FEngineVertex{ FVector(0.0f, -1.0f, 0.0f), {0.5f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[2] = FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {1.0f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} };

		Vertexs[3] = FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.5f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[4] = FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {1.0f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[5] = FEngineVertex{ FVector(0.0f, 1.0f, 0.0f), {0.5f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f} };

		Vertexs[6] = FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.5f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[7] = FEngineVertex{ FVector(0.0f, 1.0f, 0.0f), {0.5f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[8] = FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} };

		Vertexs[9] = FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.5f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[10] = FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[11] = FEngineVertex{ FVector(0.0f, -1.0f, 0.0f), {0.5f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} };

		Vertexs[12] = FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.5f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[13] = FEngineVertex{ FVector(0.0f, -1.0f, 0.0f), {0.5f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[14] = FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {1.0f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} };

		Vertexs[15] = FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.5f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[16] = FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {1.0f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[17] = FEngineVertex{ FVector(0.0f, 1.0f, 0.0f), {0.5f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} };

		Vertexs[18] = FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.5f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[19] = FEngineVertex{ FVector(0.0f, 1.0f, 0.0f), {0.5f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[20] = FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f} };

		Vertexs[21] = FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.5f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[22] = FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[23] = FEngineVertex{ FVector(0.0f, -1.0f, 0.0f), {0.5f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} };


		UEngineVertexBuffer::Create("Crystal", Vertexs);

		std::vector<uint32_t> Indices;
		Indices.push_back(0);
		Indices.push_back(1);
		Indices.push_back(2);

		Indices.push_back(3);
		Indices.push_back(5);
		Indices.push_back(4);

		Indices.push_back(6);
		Indices.push_back(7);
		Indices.push_back(8);

		Indices.push_back(9);
		Indices.push_back(10);
		Indices.push_back(11);

		Indices.push_back(12);
		Indices.push_back(13);
		Indices.push_back(14);

		Indices.push_back(15);
		Indices.push_back(16);
		Indices.push_back(17);

		Indices.push_back(18);
		Indices.push_back(19);
		Indices.push_back(20);

		Indices.push_back(21);
		Indices.push_back(23);
		Indices.push_back(22);

		UEngineIndexBuffer::Create("Crystal", Indices);
		UMesh::Create("Crystal");
	}



	

	


}

void UEngineGraphicDevice::BlendInit()
{


	D3D11_BLEND_DESC Desc = { 0 };


	Desc.AlphaToCoverageEnable = false;

	Desc.IndependentBlendEnable = true;
	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;




	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	UEngineBlend::Create("AlphaBlend", Desc);
}

void UEngineGraphicDevice::RasterizerStateInit()
{
	{
		D3D11_RASTERIZER_DESC Desc = {};
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		UEngineRasterizerState::Create("EngineBase", Desc);
	}

	{
		D3D11_RASTERIZER_DESC Desc = {};
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;

		UEngineRasterizerState::Create("CollisionDebugRas", Desc);
	}
}

void UEngineGraphicDevice::MaterialInit()
{
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("SpriteMaterial");
		Mat->SetVertexShader("EngineSpriteShader.fx");
		Mat->SetPixelShader("EngineSpriteShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("WidgetMaterial");
		Mat->SetVertexShader("EngineSpriteShader.fx");
		Mat->SetPixelShader("EngineSpriteShader.fx");
		Mat->SetDepthStencilState("UIDepth");
	}


	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("CollisionDebugMaterial");
		Mat->SetVertexShader("EngineDebugCollisionShader.fx");
		Mat->SetPixelShader("EngineDebugCollisionShader.fx");
		Mat->SetDepthStencilState("CollisionDebugDepth");
		Mat->SetRasterizerState("CollisionDebugRas");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("TileMap");
		Mat->SetVertexShader("EngineTileMapShader.fx");
		Mat->SetPixelShader("EngineTileMapShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("TargetMerge");
		Mat->SetVertexShader("EngineTargetMergeShader.fx");
		Mat->SetPixelShader("EngineTargetMergeShader.fx");
		Mat->SetDepthStencilState("TargetMerge");
	}





}