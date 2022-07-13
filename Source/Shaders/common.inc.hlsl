#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED

#define SIZEOF_UINT  4
#define SIZEOF_UINT2 8
#define SIZEOF_UINT3 12
#define SIZEOF_UINT4 16
#define SIZEOF_DRAW_INDIRECT_ARGUMENTS 16

float2 OctWrap(float2 v)
{
    return (1.0 - abs(v.yx)) * (select(v.xy >= 0.0, 1.0, -1.0));
}

float2 OctNormalEncode(float3 n)
{
    n /= (abs(n.x) + abs(n.y) + abs(n.z));
    n.xy = n.z >= 0.0 ? n.xy : OctWrap(n.xy);
    n.xy = n.xy * 0.5 + 0.5;
    return n.xy;
}

float3 OctNormalDecode(float2 f)
{
    f = f * 2.0 - 1.0;

    // https://twitter.com/Stubbesaurus/status/937994790553227264
    float3 n = float3(f.x, f.y, 1.0 - abs(f.x) - abs(f.y));
    float t = saturate(-n.z);
    n.xy += select(n.xy >= 0.0, -t, t);
    return normalize(n);
}

float LinearizeDepth(float d, float zNear, float zFar)
{
    float z_n = 2.0 * d - 1.0;
    return 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
}

float Map(float value, float originalMin, float originalMax, float newMin, float newMax)
{
    return (value - originalMin) / (originalMax - originalMin) * (newMax - newMin) + newMin;
}

float4 ToFloat4(int input, float defaultAlphaVal)
{
    return float4(input, 0, 0, defaultAlphaVal);
}

float4 ToFloat4(int2 input, float defaultAlphaVal)
{
    return float4(input, 0, defaultAlphaVal);
}

float4 ToFloat4(int3 input, float defaultAlphaVal)
{
    return float4(input, defaultAlphaVal);
}

float4 ToFloat4(int4 input, float defaultAlphaVal)
{
    return float4(input);
}

float4 ToFloat4(uint input, float defaultAlphaVal)
{
    return float4(input, 0, 0, defaultAlphaVal);
}

float4 ToFloat4(uint2 input, float defaultAlphaVal)
{
    return float4(input, 0, defaultAlphaVal);
}

float4 ToFloat4(uint3 input, float defaultAlphaVal)
{
    return float4(input, defaultAlphaVal);
}

float4 ToFloat4(uint4 input, float defaultAlphaVal)
{
    return float4(input);
}

float4 ToFloat4(float input, float defaultAlphaVal)
{
    return float4(input, 0, 0, defaultAlphaVal);
}

float4 ToFloat4(float2 input, float defaultAlphaVal)
{
    return float4(input, 0, defaultAlphaVal);
}

float4 ToFloat4(float3 input, float defaultAlphaVal)
{
    return float4(input, defaultAlphaVal);
}

float4 ToFloat4(float4 input, float defaultAlphaVal)
{
    return input;
}

struct Draw
{
    uint indexCount;
    uint instanceCount;
    uint firstIndex;
    uint vertexOffset;
    uint firstInstance;
};

void WriteDrawToByteAdressBuffer(RWByteAddressBuffer byteAddressBuffer, uint drawOffset, Draw draw)
{
    uint byteOffset = drawOffset * sizeof(Draw);

    byteAddressBuffer.Store4(byteOffset, uint4(draw.indexCount, draw.instanceCount, draw.firstIndex, draw.vertexOffset));
    byteAddressBuffer.Store(byteOffset + (4 * sizeof(uint)), draw.firstInstance);
}

// This assumes the float components are between 0 and 1, and it will be stored as a unorm
uint Float4ToPackedUnorms(float4 f)
{
    uint packed = 0;
    packed |= uint(f.x * 255) << 0;
    packed |= uint(f.y * 255) << 8;
    packed |= uint(f.z * 255) << 16;
    packed |= uint(f.w * 255) << 24;
    return packed;
}

float4 PackedUnormsToFloat4(uint packed)
{
    float4 f = 0;
    f.x = ((packed >> 0) & 0xFF) / 255.0f;
    f.y = ((packed >> 8) & 0xFF) / 255.0f;
    f.z = ((packed >> 16) & 0xFF) / 255.0f;
    f.w = ((packed >> 24) & 0xFF) / 255.0f;
    return f;
}

#endif // COMMON_INCLUDED