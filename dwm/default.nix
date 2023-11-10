{
  stdenv,
  libX11,
  xorg,
}:
stdenv.mkDerivation (finalAttrs: {
  pname = "dwm";
  version = "6.4";

  src = ./.;

  buildInputs = [
    libX11
    xorg.libXft
    xorg.libXinerama
  ];

  prePatch = ''
    sed -i "s@PREFIX = /usr@PREFIX = $out@g" config.mk
  '';

  meta.mainProgram = "dwm";
})
