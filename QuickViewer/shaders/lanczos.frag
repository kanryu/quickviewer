const int BLOCK = 8;

uniform vec2 offsets[BLOCK];
uniform vec4 kernel[BLOCK];



lowp vec4 customShader(lowp sampler2D sampler, highp vec2 texcoord0) {
    mediump vec4 midline[BLOCK];
    //   0   1 ... 14 15 16 17 ... 19 30
    // -15 -14 ... -1  0  1  2 ... 14 15
    mediump vec4 sum = texture2D(sampler, texcoord0.st) * kernel[0];
    for (int i = 1; i < BLOCK; i++) {
        sum += ( texture2D(sampler, texcoord0.st - offsets[i])
               + texture2D(sampler, texcoord0.st + offsets[i]) ) * kernel[i];
    }
    midline[0] = sum;
    for (int j = 1; j < BLOCK; j++) {
        mediump vec2 ofs = vec2(0, offsets[j].x);
        mediump vec4 sum2 = (  texture2D(sampler, texcoord0.st - ofs)
                             + texture2D(sampler, texcoord0.st + ofs) ) * kernel[0];
        for (int i = 1; i < BLOCK; i++) {
            sum2 += (  texture2D(sampler, texcoord0.st - offsets[i] - ofs)
                     + texture2D(sampler, texcoord0.st + offsets[i] - ofs)
                     + texture2D(sampler, texcoord0.st - offsets[i] + ofs)
                     + texture2D(sampler, texcoord0.st + offsets[i] + ofs) ) * kernel[i];
        }
        midline[j] = sum2;
    }
    mediump vec4 sum4 = midline[0] * kernel[0];
    for (int i = 1; i < BLOCK; i++) {
        sum4 += midline[i] * kernel[i];
    }
    return sum4;
}
