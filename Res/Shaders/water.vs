#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;

// Input uniform values
uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;

// Output vertex attributes (to fragment shader)
out vec3 fragPosition;
out vec2 fragTexCoord;
out vec4 fragColor;
out vec3 fragNormal;
out vec3 fPosition;

uniform float time;

// NOTE: Add here your custom variables

void main()
{
    // Send vertex attributes to fragment shader
    fragPosition = vec3(matModel*vec4(vertexPosition, 1.0));
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    fragNormal = normalize(vec3(matNormal*vec4(vertexNormal, 1.0)));
    vec4 pos = mvp*vec4(vertexPosition, 1.0);
    fPosition = pos.xyz;
    float speed = 2.0;
    float a = 2.0;
    fragPosition.y = max(cos((fragPosition.x * a) + (time * speed)), 0.01);
    
    // Calculate final vertex position
    gl_Position = mvp*vec4(fragPosition, 1.0);
    
}