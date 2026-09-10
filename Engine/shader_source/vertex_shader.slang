typealias vec1 = float;
typealias vec2 = float2;
typealias vec3 = float3;
typealias vec4 = float4;

struct VSInput
{
    [[vk::location(0)]] vec2 position;
    [[vk::location(1)]] vec3 rgb;
};

struct VSOutput
{
    float4 position : SV_Position;
    [[vk::location(0)]] float3 fragColor;
};

[shader("vertex")]
VSOutput main(VSInput input)
{
    VSOutput output;
    output.position = float4(input.position, 0.0, 1.0);
    output.fragColor = input.rgb;
    return output;
}
