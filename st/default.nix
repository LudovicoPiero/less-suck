{
  stdenv,
  libX11,
  xorg,
  pkg-config,
  ncurses,
}:
stdenv.mkDerivation (finalAttrs: {
  pname = "st";
  version = "0.9";

  src = ./.;

  nativeBuildInputs = [
    ncurses
    pkg-config
  ];

  buildInputs = [
    libX11
    xorg.libXft
  ];

  preInstall = ''
    export TERMINFO=$out/share/terminfo
  '';

  prePatch = ''
    sed -i "s@PREFIX = /usr/local@PREFIX = $out@g" config.mk
  '';

  meta.mainProgram = "st";
})
