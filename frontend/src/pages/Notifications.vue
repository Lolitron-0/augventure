<template>
  <div class="notifications">
    <p class="text2">Notifications</p>
  </div>
</template>

<script>
export default {

}
</script>

<style scoped>
@import "@/styles.css";

.notifications{
  background-color: var(--background-app-color);
  width: 100vw;
  height: 100vh;
  position: relative;
  justify-content: center;
  align-items: center;
}
.text2{
  color: red;
  top: 150px;
  left: 300px;
  position: absolute;
  font-size: 28px;
}
</style>