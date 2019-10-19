#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/VertexColor.h>
#include <Magnum/Text/AbstractFont.h>
#include <Magnum/Text/DistanceFieldGlyphCache.h>
#include <Magnum/Text/Renderer.h>
#include <Corrade/PluginManager/Manager.h>

namespace Magnum { namespace Examples {

class TriangleExample: public Platform::Application {
 public:
  explicit TriangleExample(const Arguments& arguments);

 private:
  void drawEvent() override;

  GL::Mesh _mesh;
  Shaders::VertexColor2D _shader;
  PluginManager::Manager<Text::AbstractFont> _manager;
  std::unique_ptr<Text::AbstractFont> _font;
  Text::DistanceFieldGlyphCache _cache;
  GL::Buffer _vertices, _indices;
  GL::Mesh _text;
};

TriangleExample::TriangleExample(const Arguments& arguments):
    Platform::Application{arguments, Configuration{}.setTitle("Magnum Triangle Example")},
    _cache(Vector2i(2048), Vector2i(512), 22)
{

  _font = _manager.loadAndInstantiate("FreeTypeFont");
  if(!_font) std::exit(1);

  /* Open the font and fill glyph cache */
  Utility::Resource rs("fonts");
  auto dejavu = rs.getRaw("DejaVuSans.ttf");
  if(!_font->openData({{"DejaVuSans.ttf", dejavu}}, 110.0f)) {
    Error() << "Cannot open font file";
    std::exit(1);
  }
  _font->fillGlyphCache(_cache, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:-+,.!°ěäЗдравстуймиΓειασουκόμ ");
  std::tie(_text, std::ignore) = Text::Renderer2D::render(*_font, _cache, 0.1295f,
                                                          "Hello, world!\n"
                                                          "Ahoj, světe!\n"
                                                          "Здравствуй, мир!\n"
                                                          "Γεια σου κόσμε!\n"
                                                          "Hej Världen!",
                                                          _vertices, _indices, GL::BufferUsage::StaticDraw, Text::Alignment::MiddleCenter);
  using namespace Math::Literals;

  struct TriangleVertex {
    Vector2 position;
    Color3 color;
  };
  const TriangleVertex data[]{
      {{-0.5f, -0.5f}, 0xff0000_rgbf},    /* Left vertex, red color */
      {{ 0.5f, -0.5f}, 0x00ff00_rgbf},    /* Right vertex, green color */
      {{ 0.0f,  0.5f}, 0x0000ff_rgbf}     /* Top vertex, blue color */
  };

  GL::Buffer buffer;
  buffer.setData(data);

  _mesh.setCount(3)
      .addVertexBuffer(std::move(buffer), 0,
                       Shaders::VertexColor2D::Position{},
                       Shaders::VertexColor2D::Color3{});
}

void TriangleExample::drawEvent() {
  GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

  _mesh.draw(_shader);

  swapBuffers();
}

}}

MAGNUM_APPLICATION_MAIN(Magnum::Examples::TriangleExample)