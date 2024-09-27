cd ai_help/
chmod +x keygen.sh
./keygen.sh
chmod +x unifier.sh
find key/ ! -name "*.key" -type f -delete
./unifier.sh
