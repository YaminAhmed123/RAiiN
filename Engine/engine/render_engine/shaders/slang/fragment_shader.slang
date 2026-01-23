struct VSInput {
    float3 color : COLOR0;
};

struct FSOutput {
    float4 color : SV_Target0;
};

[shader("fragment")]
FSOutput main(VSInput input) {
    FSOutput output;
    output.color = float4(input.color, 1.0); // Output the interpolated color
    return output;
}