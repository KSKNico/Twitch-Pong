{ stdenv, cmake, sfml }:
stdenv.mkDerivation {
  name = "twitch-pong";
  src = ./.;
  nativeBuildInputs = [ cmake ];
  buildInputs = [ sfml ];
}
