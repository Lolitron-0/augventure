<template>
  <div class="home">
    <h1 class="title">Title</h1>
  </div>
</template>

<script>
export default {
  emits: ['updateCurrentPage'],
  created() {
    this.main();
  },
  methods: {
    main() {
      this.$emit('updateCurrentPage', 'main');
      console.log("main page event triggered");
    }
  }
}
</script>

<style scoped>
@import "@/styles.css";
* {
  margin: 0;
  padding: 0;
}
.home{
  background-color: var(--background-app-color);
  width: 100vw;
  height: 100vh;
  position: relative;
  justify-content: center;
  align-items: center;
}
.title{
  color: red;
  top: 150px;
  left: 300px;
  position: absolute;
  font-size: 28px;
}
</style>