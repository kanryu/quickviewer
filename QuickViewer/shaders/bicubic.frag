#version 330


vec4 customShader(sampler2D sampler, highp vec2 coord) {
    vec2 res = textureSize(sampler, 0);

    coord = coord * res - 0.5;

    highp vec2 f = fract(coord);
    coord -= f;

    highp vec2 ff = f * f;
    highp vec4 w0;
    highp vec4 w1;
    w0.xz = 1 - f; w0.xz *= w0.xz * w0.xz;
    w1.yw = ff * f;
    w1.xz = 3 * w1.yw + 4 - 6 * ff;
    w0.yw = 6 - w1.xz - w1.yw - w0.xz;

    highp vec4 s = w0 + w1;
    highp vec4 c = coord.xxyy + vec2(-0.5, 1.5).xyxy + w1 / s;
    c /= res.xxyy;

    vec2 m = s.xz / (s.xz + s.yw);
    return mix(
        mix(texture2D(sampler, c.yw), texture2D(sampler, c.xw), m.x),
        mix(texture2D(sampler, c.yz), texture2D(sampler, c.xz), m.x),
        m.y);
}
