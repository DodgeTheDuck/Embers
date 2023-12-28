#version 420 core

out vec4 o_frag_color;

in vec3 frag_pos_world;
in vec2 frag_uv;
in vec3 frag_normal;

uniform vec3 u_camera_pos;

layout(binding = 0) uniform sampler2D u_albedo;
layout(binding = 1) uniform sampler2D u_normal;
layout(binding = 2) uniform sampler2D u_metallic;
layout(binding = 3) uniform sampler2D u_roughness;
layout(binding = 4) uniform sampler2D u_metallic_roughness;
layout(binding = 5) uniform sampler2D u_ao;

const float PI = 3.14159265359;

// ----------------------------------------------------------------------------
// Easy trick to get tangent-normals to world-space to keep PBR code simplified.
// Don't worry if you don't get what's going on; you generally want to do normal 
// mapping the usual way for performance anyways; I do plan make a note of this 
// technique somewhere later in the normal mapping tutorial.
vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(u_normal, frag_uv).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(frag_pos_world);
    vec3 Q2  = dFdy(frag_pos_world);
    vec2 st1 = dFdx(frag_uv);
    vec2 st2 = dFdy(frag_uv);

    vec3 N   = normalize(frag_normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main()
{

    float exposure = 0.8;

    vec3 lightPos = vec3(3, 3, 5);
    vec3 lightCol = vec3(1024, 1024, 1024);    

    vec3 tex_albedo = pow(texture(u_albedo, frag_uv).rgb, vec3(exposure));
    vec4 tex_metallic = texture2D(u_metallic, frag_uv);
    vec4 tex_roughness = texture2D(u_roughness, frag_uv);
    vec4 tex_metallic_roughness = texture2D(u_metallic_roughness, frag_uv);

    float metallic = tex_metallic_roughness.r;
    float roughness = tex_metallic_roughness.g;
    float ao = texture(u_ao, frag_uv).r;

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, tex_albedo, metallic);
    vec3 Lo = vec3(0.0);

    vec3 N = getNormalFromMap();
    vec3 V = normalize(u_camera_pos - frag_pos_world);
    vec3 L = normalize(lightPos - frag_pos_world);
    vec3 H = normalize(V + L);
    float distance = length(lightPos - frag_pos_world);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = lightCol * attenuation;

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(N, H, roughness);
    float G   = GeometrySmith(N, V, L, roughness);      
    vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
           
    vec3 numerator    = NDF * G * F; 
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
    vec3 specular = numerator / denominator;
        
    // kS is equal to Fresnel
    vec3 kS = F;
    // for energy conservation, the diffuse and specular light can't
    // be above 1.0 (unless the surface emits light); to preserve this
    // relationship the diffuse component (kD) should equal 1.0 - kS.
    vec3 kD = vec3(1.0) - kS;
    // multiply kD by the inverse metalness such that only non-metals 
    // have diffuse lighting, or a linear blend if partly metal (pure metals
    // have no diffuse light).
    kD *= 1.0 - metallic;	  

    // scale light by NdotL
    float NdotL = max(dot(N, L), 0.0);        

    // add to outgoing radiance Lo
    Lo += (kD * tex_albedo / PI + specular) * radiance * NdotL;

    vec3 ambient = vec3(0.03) * tex_albedo * ao;
    
    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/exposure)); 

    o_frag_color = vec4(color, 1.0);

} 