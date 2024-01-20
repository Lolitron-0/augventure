<template>
  <button class="btn">
    <slot></slot>
  </button>
</template>

<script>
export default {

}
</script>

<style scoped>
  .btn {
    //display: inline-block;
    display: flex;
    //font-size: 14px;
    letter-spacing: 1px;
    background: #081b29;
    //padding: 10px 30px;
    text-decoration: none;
    //text-transform: uppercase;
    border-radius: 10px;
    transition: .6s;
    //border: none;
    cursor: pointer;
  }

  .btn:hover {
    background-color: #31a0a8;
  }
</style>