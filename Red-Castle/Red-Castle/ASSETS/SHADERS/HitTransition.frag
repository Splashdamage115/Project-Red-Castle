// transition.frag
uniform sampler2D texture;
uniform float time;
uniform float duration;

void main() {
    vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);
    float factor = abs(sin(time * 3.14159 / duration)); // Transition over the duration
    vec4 whiteColor = vec4(1.0, 1.0, 1.0, texColor.a);
    gl_FragColor = mix(texColor, whiteColor, factor);
}