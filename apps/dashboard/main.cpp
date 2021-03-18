#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Math/Complex.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix3.h>
#include <Magnum/Shaders/VertexColor.h>
#include <Magnum/Shaders/DistanceFieldVector.h>
#include <Magnum/Text/AbstractFont.h>
#include <Magnum/Text/DistanceFieldGlyphCache.h>
#include <Magnum/Text/Renderer.h>
#include <Corrade/Utility/Format.h>
#include <Corrade/Utility/Resource.h>
#include <Corrade/PluginManager/Manager.h>
#include <fmt/format.h>

#include <memory>

namespace Magnum::Examples {
    using namespace Math::Literals;

    class TriangleExample : public Platform::Application {
    public:
        explicit TriangleExample(const Arguments& arguments);

    private:
        void viewportEvent(ViewportEvent& event) override;

        void drawEvent() override;

        void updateText();

        void mouseScrollEvent(MouseScrollEvent& event) override;

        GL::Mesh _mesh;
        Shaders::VertexColor2D _shader;
        Shaders::DistanceFieldVector2D _text_shader;

        PluginManager::Manager<Text::AbstractFont> _manager;
        std::unique_ptr<Text::AbstractFont> _font;
        std::unique_ptr<Text::Renderer2D> _dynamicText;
        Text::DistanceFieldGlyphCache _cache;
        GL::Buffer _vertices, _indices;
        GL::Mesh _text;

        Matrix3 _transformationRotatingText,
                _projectionRotatingText,
                _transformationProjectionDynamicText;
    };

    TriangleExample::TriangleExample(const Arguments& arguments) :
            Platform::Application{arguments, Configuration{}.setTitle("Magnum Triangle Example")},
            _cache(Vector2i(2048), Vector2i(512), 22) {

        _font = _manager.loadAndInstantiate("FreeTypeFont");
        if (!_font) std::exit(1);

        /* Open the font and fill glyph cache */
        Utility::Resource rs("fonts");
        auto dejavu = rs.getRaw("DejaVuSans.ttf");
        if (!_font->openData({{"DejaVuSans.ttf", dejavu}}, 110.0f)) {
            Error() << "Cannot open font file";
            std::exit(1);
        }
        _font->fillGlyphCache(_cache,
                              "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:-+,.!°ěäЗдравстуймиΓειασουκόμ ");
        std::tie(_text, std::ignore) = Text::Renderer2D::render(
                *_font, _cache, 0.1295f,
                "Hello, world!\n"
                "Ahoj, světe!\n"
                "Здравствуй, мир!\n"
                "Γεια σου κόσμε!\n"
                "Hej Världen!",
                _vertices, _indices, GL::BufferUsage::StaticDraw, Text::Alignment::MiddleCenter);

        _transformationRotatingText = Matrix3::rotation(-10.0_degf);
        _projectionRotatingText = Matrix3::projection(
                Vector2::xScale(Vector2{windowSize()}.aspectRatio()));

        /* Dynamically updated text that shows rotation/zoom of the other. Size in
           points that stays the same if you resize the window. Aligned so top
           right of the bounding box is at mesh origin, and then transformed so the
           origin is at the top right corner of the window. */
        _dynamicText = std::make_unique<Text::Renderer2D>(*_font, _cache, 32.0f, Text::Alignment::TopRight);
        _dynamicText->reserve(40, GL::BufferUsage::DynamicDraw, GL::BufferUsage::StaticDraw);
        _transformationProjectionDynamicText =
                Matrix3::projection(Vector2{windowSize()}) *
                Matrix3::translation(Vector2{windowSize()} * 0.5f);

        /* Set up premultiplied alpha blending to avoid overlapping text characters
           to cut into each other */
        GL::Renderer::enable(GL::Renderer::Feature::Blending);
        GL::Renderer::setBlendFunction(GL::Renderer::BlendFunction::One,
                                       GL::Renderer::BlendFunction::OneMinusSourceAlpha);
        GL::Renderer::setBlendEquation(GL::Renderer::BlendEquation::Add, GL::Renderer::BlendEquation::Add);

        updateText();

        struct TriangleVertex {
            Vector2 position;
            Color3 color;
        };
        const TriangleVertex data[]{
                {{-0.5f, -0.5f}, 0xff0000_rgbf},    /* Left vertex, red color */
                {{0.5f,  -0.5f}, 0x00ff00_rgbf},    /* Right vertex, green color */
                {{0.0f,  0.5f},  0x0000ff_rgbf}     /* Top vertex, blue color */
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

        _text_shader.bindVectorTexture(_cache.texture());

        _text_shader
                .setTransformationProjectionMatrix(
                        _projectionRotatingText * _transformationRotatingText)
                .setColor(0x2f83cc_rgbf)
                .setOutlineColor(0xdcdcdc_rgbf)
                .setOutlineRange(0.45f, 0.35f)
                .setSmoothness(0.025f / _transformationRotatingText.uniformScaling());
        _text.draw(_text_shader);

        _text_shader
                .setTransformationProjectionMatrix(_transformationProjectionDynamicText)
                .setColor(0xffffff_rgbf)
                .setOutlineRange(0.5f, 1.0f)
                .setSmoothness(0.075f);
        _dynamicText->mesh().draw(_text_shader);

        swapBuffers();
    }

    void TriangleExample::mouseScrollEvent(MouseScrollEvent& event) {
        if (!event.offset().y()) return;

        if (event.offset().y() > 0)
            _transformationRotatingText =
                    Matrix3::rotation(1.0_degf) * Matrix3::scaling(Vector2{1.1f}) * _transformationRotatingText;
        else
            _transformationRotatingText =
                    Matrix3::rotation(-1.0_degf) * Matrix3::scaling(Vector2{1.0f / 1.1f}) * _transformationRotatingText;

        updateText();

        event.setAccepted();
        redraw();
    }

    void TriangleExample::updateText() {
        _dynamicText->render(fmt::format("Rotation: {:.2}°\nScale: {:.2}",
                                                   Float(Deg(Magnum::Math::Complex<float>::fromMatrix(
                                                           _transformationRotatingText.rotation()).angle())),
                                                   _transformationRotatingText.uniformScaling()));
    }

    void TriangleExample::viewportEvent(ViewportEvent& event) {
        GL::defaultFramebuffer.setViewport({{}, event.framebufferSize()});

        _projectionRotatingText = Matrix3::projection(
                Vector2::xScale(Vector2{windowSize()}.aspectRatio()));
        _transformationProjectionDynamicText =
                Matrix3::projection(Vector2{windowSize()}) *
                Matrix3::translation(Vector2{windowSize()} * 0.5f);
    }

}

MAGNUM_APPLICATION_MAIN(Magnum::Examples::TriangleExample)