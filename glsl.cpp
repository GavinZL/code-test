
#include <string>

#define GLSL_PREFIX  "#version 300 es \n precision highp float;\n"
#define GLSL(shader_str) "#version 300 es \n precision highp float;\n" #shader_str



static const std::string comm_vert = GLSL(
in vec2 a_position;
in vec2 a_tex;
out vec2 o_tex;
void main(){
    o_tex = a_tex;
    //o_tex.y = 1.0 - o_tex.y;
    gl_Position = vec4(a_position, 0.0, 1.0);
});

static const std::string nv12_frag = GLSL(
in vec2 o_tex;
uniform sampler2D s_inputY;
uniform sampler2D s_inputUV;
uniform mat3 colorConversionMatrix;
out vec4 fragColor;
void main()
{
    vec3 yuv;
    vec3 rgb;
    yuv.x = texture(s_inputY, o_tex).r - 0.00392;//16.0/255
    yuv.yz = (texture(s_inputUV, o_tex).ra - vec2(0.5, 0.5));
    if(o_tex.x < 0.5){
        rgb = colorConversionMatrix * yuv;
    }else{
        rgb = vec3(0.0, 1.0, 0.0);
    }
    fragColor = vec4(0.0, 0.0, 1.0, 1.0);//vec4(rgb, 1);
});